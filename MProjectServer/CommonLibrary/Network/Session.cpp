#include "Session.h"

#include "IOService.h"
#include "Core/MLogger.h"

FSession::FSession(std::shared_ptr<IOService> _IO_service, ESessionType _session_type, size_t _send_buffer_size, size_t _recv_buffer_size, int _max_packet_size)
	: top_IO_service(_IO_service), sock(_IO_service->GetIOService()), strand(_IO_service->GetIOService()),
		session_key(0), session_type(_session_type), sequence_type(ESequenceType::Disconnected),
		public_ip(), public_port(),
		buffer_pool(BUFFER_BLOCKS_PER_BUCKET, BUFFER_BLOCKS_PER_BUCKET), send_buffer(nullptr), recv_buffer(nullptr), send_buffers(_send_buffer_size), recv_buffers(_recv_buffer_size),
		max_packet_size(_max_packet_size), is_writing(false) {

}

FSession::~FSession() {
	boost::system::error_code error_code;
	sock.close(error_code);
	//! send_buffer, recv_buffer는 메모리풀에 의해 자동으로 메모리 해체됨
}

void FSession::Accept(SessionKey _session_key) {
	session_key = _session_key;
	sequence_type = ESequenceType::Connected;
	send_buffers.Discard(send_buffers.UsedSize());
	recv_buffers.Discard(recv_buffers.UsedSize());
	
	if (nullptr != send_buffer) {
		buffer_pool.Release(send_buffer);
		send_buffer = nullptr;
	}

	if (nullptr != recv_buffer) {
		buffer_pool.Release(recv_buffer);
		recv_buffer = nullptr;
	}

	
	boost::asio::ip::tcp::no_delay no_delay(true);
	GetSocket().set_option(no_delay);
	

	Receive();
}

void FSession::Connect(SessionKey _session_key) {
	session_key = _session_key;
	sequence_type = ESequenceType::Connected;
	send_buffers.Discard(send_buffers.UsedSize());
	recv_buffers.Discard(recv_buffers.UsedSize());

	if (nullptr != send_buffer) {
		buffer_pool.Release(send_buffer);
		send_buffer = nullptr;
	}

	if (nullptr != recv_buffer) {
		buffer_pool.Release(recv_buffer);
		recv_buffer = nullptr;
	}
	
	
	boost::asio::ip::tcp::no_delay no_delay(true);
	GetSocket().set_option(no_delay);
	

	Receive();
}

void FSession::Disconnect() {
	sequence_type = ESequenceType::Disconnected;
	send_buffers.Discard(send_buffers.UsedSize());
	recv_buffers.Discard(recv_buffers.UsedSize());

	if (nullptr != send_buffer) {
		buffer_pool.Release(send_buffer);
		send_buffer = nullptr;
	}

	if (nullptr != recv_buffer) {
		buffer_pool.Release(recv_buffer);
		recv_buffer = nullptr;
	}

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
	recv_buffer = reinterpret_cast<byte*>(buffer_pool.Get());
	
	GetSocket().async_read_some(
		boost::asio::buffer(recv_buffer, free_size),
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

void FSession::Write(size_t _size) {
	if (GetSequenceType() != ESequenceType::Connected) {
		return;
	}

	if (_size > max_packet_size) {
		top_IO_service->PushNetEvent(ENetEventType::Error, shared_from_this());
		return;
	}
	
	if (false == IsWriting()) {
		if (nullptr != send_buffer) {
			buffer_pool.Release(send_buffer);
		}

		//size_t used_size = recv_buffers.UsedSize();
		size_t used_size = send_buffers.UsedSize();
		
		send_buffer = reinterpret_cast<byte*>(buffer_pool.Get());
		//recv_buffers.Peek(send_buffer, used_size);
		send_buffers.Peek(send_buffer, used_size);

		SetWriting(true);
		
		GetSocket().async_write_some(
			boost::asio::buffer(send_buffer, used_size),
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

#include <boost/locale.hpp>

void FSession::OnReceive(boost::system::error_code const& _error_code, size_t _bytes_transferred) {
	if (_error_code != boost::system::errc::success) {
		MLogger::GetMutableInstance().LogError(std::format("[{}]{} - code:{}", _error_code.category().name(), _error_code.message(), _error_code.value()));
		return;
	}
	
	std::string a = boost::locale::conv::utf_to_utf<char>(recv_buffer, recv_buffer + _bytes_transferred);
	MLogger::GetMutableInstance().LogInfo(a);

	recv_buffers.Put(recv_buffer, _bytes_transferred);
	buffer_pool.Release(recv_buffer);
	recv_buffer = nullptr;
	
	//Write(_bytes_transferred);
	Receive();
}

void FSession::OnWrite(boost::system::error_code const& _error_code, size_t _bytes_transferred) {
	if (_error_code != boost::system::errc::success) {
		SetWriting(false);
		return;
	}

	//recv_buffers.Discard(_bytes_transferred);
	send_buffers.Discard(_bytes_transferred);

	if (0 == send_buffers.UsedSize()) { // changed send_buffer
		SetWriting(false);
		return;
	}

	if (nullptr != send_buffer) {
		buffer_pool.Release(send_buffer);
	}
	
	//size_t used_size = recv_buffers.UsedSize();
	size_t used_size = send_buffers.UsedSize();
	send_buffer = reinterpret_cast<byte*>(buffer_pool.Get());
	//recv_buffers.Peek(send_buffer, used_size);
	send_buffers.Peek(send_buffer, used_size);

	GetSocket().async_write_some(
		boost::asio::buffer(send_buffer, used_size),
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

void FSession::Execute() {
	
	
}
