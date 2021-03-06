#include "Session.h"

#include "IOService.h"
#include "Core/LogManager.h"
#include "BaseProtocol.h"
#include "NetworkToolkit.h"
#include "Utility/UniversalToolkit.h"


FSession::FSession(std::shared_ptr<IOService> _IO_service, ESessionType _session_type, size_t _send_buffer_size, size_t _recv_buffer_size, int _max_packet_size)
	: top_IO_service(_IO_service), sock(_IO_service->GetIOService()), strand(_IO_service->GetIOService()),
		session_key(0), session_type(_session_type), sequence_type(ESequenceType::Disconnected),
		public_ip(), public_port(),
		buffer_pool(PACKET_MAX_SIZE, PACKET_PRE_ALLOC_SIZE), send_packet(&buffer_pool), recv_packet(&buffer_pool), send_packet_queue(new SPSCQueue<std::unique_ptr<FPacket>>(NET_SEND_PACKET_COUNT)), recv_buffers(_recv_buffer_size),
		max_packet_size(_max_packet_size), is_writing(false) {

}

FSession::~FSession() {
	boost::system::error_code error_code;
	sock.close(error_code);
	//! 버퍼 데이터는 메모리풀에 의해 자동으로 메모리 해제됨
}

void FSession::Accept(SessionKey _session_key) {
	session_key = _session_key;
	sequence_type = ESequenceType::Connected;
	send_packet.Relase();
	recv_packet.Relase();
	while (false == send_packet_queue->empty()) { send_packet_queue->pop(); }
	recv_buffers.Discard(recv_buffers.UsedSize());

	
	boost::asio::ip::tcp::no_delay no_delay(true);
	GetSocket().set_option(no_delay);
	

	Receive();
}

void FSession::Connect(SessionKey _session_key) {
	session_key = _session_key;
	sequence_type = ESequenceType::Connected;
	send_packet.Relase();
	recv_packet.Relase();
	while (false == send_packet_queue->empty()) { send_packet_queue->pop(); }
	recv_buffers.Discard(recv_buffers.UsedSize());
	
	
	boost::asio::ip::tcp::no_delay no_delay(true);
	GetSocket().set_option(no_delay);
	

	Receive();
}

void FSession::Disconnect() {
	sequence_type = ESequenceType::Disconnected;
	send_packet.Relase();
	recv_packet.Relase();
	while (false == send_packet_queue->empty()) { send_packet_queue->pop(); }
	recv_buffers.Discard(recv_buffers.UsedSize());
}

void FSession::Shutdown() {
	top_IO_service->GetIOService().post(
		boost::asio::bind_executor(
			strand,
			[this]() {
				if (false == GetSocket().is_open()) {
					return;
				}
				boost::system::error_code error_code;
				GetSocket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, error_code);
				GetSocket().close(error_code);
			}
		)
	);
}

void FSession::Close() {
	top_IO_service->GetIOService().post(
		boost::asio::bind_executor(
			strand,
			[this]() {
				if (false == GetSocket().is_open()) {
					return;
				}
				boost::system::error_code error_code;
				GetSocket().close(error_code);
			}
		)
	);
}

void FSession::Receive() {
	size_t free_size = recv_buffers.FreeSize();
	recv_packet.Allocate();
	
	GetSocket().async_read_some(
		boost::asio::buffer(recv_packet.data, free_size),
		boost::asio::bind_executor(
			strand,
			boost::bind(
				&FSession::OnReceive,
				shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred
			)
		)
	);
}

void FSession::Write(std::unique_ptr<FPacket> _packet, bool _ignore/* = false */) {
	if (GetSequenceType() != ESequenceType::Connected) {
		Disconnect();
		return;
	}

	if (static_cast<int>(_packet->length + PACKET_HEADER_SIZE) > max_packet_size) {
		top_IO_service->PushNetEvent(ENetEventType::Error, shared_from_this());
		return;
	}
	
	if (true == IsWriting() && false == _ignore) {
		//! 이미 쓰기 작업을 하고 있다면 버퍼에 푸시만 해준다.
		send_packet_queue->emplace(std::move(_packet));
		return;
	} else {
		{
			int tag = _packet->tag;
			LogManager::GetMutableInstance().GenericLog(ELogLevel::Trace, "FSession", "Write", std::format("Maybe tag {0}", tag));
		}
		SetWriting(true);

		auto buffer = NetworkToolkit::GetPacketData(std::move(_packet));
		send_packet.Allocate(buffer.size());
		memcpy(send_packet.data, buffer.data(), buffer.size());
		
		GetSocket().async_write_some(
			boost::asio::buffer(send_packet.data, send_packet.length),
			boost::asio::bind_executor(
				strand,
				boost::bind(
					&FSession::OnWrite,
					shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred
				)
			)
		);
	}
}

void FSession::OnReceive(boost::system::error_code const& _error_code, size_t _bytes_transferred) {
	if (_error_code != boost::system::errc::success) {
		LogManager::GetMutableInstance().GenericLog(ELogLevel::Error, "FSession", "OnReceive", std::format("[{}]{} - code:{}", _error_code.category().name(), _error_code.message(), _error_code.value()));
		OnDisconnect();
		return;
	}
	recv_buffers.Put(recv_packet.data, _bytes_transferred);
	Receive();
}

void FSession::OnWrite(boost::system::error_code const& _error_code, size_t _bytes_transferred) {
	if (_error_code != boost::system::errc::success) {
		SetWriting(false);
		LogManager::GetMutableInstance().GenericLog(ELogLevel::Error, "FSession", "OnWrite", std::format("[{}]{} - code:{}", _error_code.category().name(), _error_code.message(), _error_code.value()));
		OnDisconnect();
		return;
	}

	if (false == send_packet.Complete(_bytes_transferred)) {
		// 만약 다 보내지 못했을 경우 나머지를 다시 보내준다.
		GetSocket().async_write_some(
			boost::asio::buffer(send_packet.data + send_packet.transferred, send_packet.length),
			boost::asio::bind_executor(
				strand,
				boost::bind(
					&FSession::OnWrite,
					shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred
				)
			)
		);
		return;
	}

	GetSocket().async_wait(
		boost::asio::ip::tcp::socket::wait_type::wait_write,
		boost::asio::bind_executor(
			strand,
			boost::bind(
				&FSession::OnWait,
				shared_from_this(),
				boost::asio::placeholders::error
			)
		)
	);
}

void FSession::OnWait(boost::system::error_code const& _error_code) {
	if (_error_code != boost::system::errc::success) {
		SetWriting(false);
		LogManager::GetMutableInstance().GenericLog(ELogLevel::Error, "FSession", "OnWrite", std::format("[{}]{} - code:{}", _error_code.category().name(), _error_code.message(), _error_code.value()));
		OnDisconnect();
		return;
	}

	if (true == send_packet_queue->empty()) {
		SetWriting(false);
		return;
	}

	std::unique_ptr<FPacket> packet = nullptr;
	while (send_packet_queue->size() > 0) {
		packet = std::move(*send_packet_queue->front());
		send_packet_queue->pop();
		if (packet == nullptr) {
			LogManager::GetMutableInstance().GenericLog(ELogLevel::Trace, "FSession", "Write", "FPacket is null");
			continue;
		}
		break;
	}
	if (nullptr == packet.get()) {
		SetWriting(false);
		return;
	}

	Write(std::move(packet), true);
}

void FSession::OnDisconnect() {
	Close();
	
	switch (sequence_type) {
		case ESequenceType::Connected: {
			sequence_type = ESequenceType::Disconnecting;
			top_IO_service->GetIOService().post(boost::bind(&IOService::PushNetEvent, top_IO_service, ENetEventType::Disconnected, shared_from_this()));
		} break;
		case ESequenceType::Disconnected: {
			// critical error
			top_IO_service->PushNetEvent(ENetEventType::Error, shared_from_this());
		} break;
		default: {
			//error
			top_IO_service->PushNetEvent(ENetEventType::Error, shared_from_this());
		} break;
	}
}

void FSession::Flush() {
	if (static_cast<uint>(recv_buffers.UsedSize()) < PACKET_HEADER_SIZE) {
		recv_buffers.Discard(recv_buffers.UsedSize());
		return;
	}

	std::unique_ptr<FPacket> packet = std::make_unique<FPacket>();
	std::vector<byte> buffer(PACKET_HEADER_SIZE);
	recv_buffers.Get(buffer.data(), PACKET_HEADER_SIZE);

	std::memcpy(&packet->tag, buffer.data(), PACKET_TAG_SIZE);
	std::memcpy(&packet->length, buffer.data() + PACKET_TAG_SIZE, PACKET_LEGNTH_SIZE);
	std::memcpy(packet->hash_code.data(), buffer.data() + PACKET_TAG_SIZE + PACKET_LEGNTH_SIZE, PACKET_HASH_CODE_SIZE);

	LogManager::GetMutableInstance().GenericLog(ELogLevel::Trace, "FSession", "Flush", std::format("Receive [{0}] Tag Packet", packet->tag));

	if (recv_buffers.UsedSize() < packet->length) {
		throw std::runtime_error("[FSession::Flush] packet length error");
	}
	
	packet->data.resize(packet->length);
	recv_buffers.Get(packet->data.data(), packet->length);
	top_IO_service->ExecuteMessage(shared_from_this(), std::move(packet));
}
