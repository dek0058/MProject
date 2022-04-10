#include "MProjectServerDefine.h"
#include "Session.h"

#include "IOService.h"

FSession::FSession(std::shared_ptr<IOService> _IO_service, ESessionType _session_type, size_t _send_buffer_size, size_t _recv_buffer_size, int _max_packet_size)
	: top_IO_service(_IO_service), sock(_IO_service->GetIOService()), strand(_IO_service->GetIOService()),
		session_key(0), session_type(_session_type), sequence_type(ESequenceType::Disconnected) ,
		send_buffers(_send_buffer_size), recv_buffers(_recv_buffer_size), max_packet_size(_max_packet_size), is_writing(false) {

}

FSession::~FSession() {
	boost::system::error_code error_code;
	sock.close(error_code);
}

void FSession::Accept(SessionKey _session_key) {
	session_key = _session_key;
	sequence_type = ESequenceType::Connected;
	send_buffers.Discard(send_buffers.UsedSize());
	recv_buffers.Discard(recv_buffers.UsedSize());

	boost::asio::ip::tcp::no_delay no_delay(true);
	GetSocket().set_option(no_delay);

	Receive();
}

void FSession::Connect(SessionKey _session_key) {
	session_key = _session_key;
	sequence_type = ESequenceType::Connected;

	boost::asio::ip::tcp::no_delay no_delay(true);
	GetSocket().set_option(no_delay);

	Receive();
}

void FSession::Disconnect() {
	sequence_type = ESequenceType::Disconnected;
	send_buffers.Discard(send_buffers.UsedSize());
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
	GetSocket().async_read_some(
		boost::asio::buffer(recv_buffer, recv_buffers.UsedSize()),
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

void FSession::Write(char* const _data, size_t _size, std::wstring const* _name) {
	if (GetSequenceType() != ESequenceType::Connected) {
		return;
	}

	if (_size > max_packet_size) {
		top_IO_service->PushNetEvent(ENetEventType::Error, shared_from_this());
		return;
	}

	
	//send_buffer = 
	//send_buffers.push_back(_data);

	if (true == IsWriting()) {
		SetWriting(true);
		
		//send_buffers.Peek(send_buffer, send_buffers.UsedSize());
		//send_buffer

		boost::asio::async_write(
			GetSocket(),
			boost::asio::buffer(send_buffer),
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
	
}

void FSession::OnWrite(boost::system::error_code const& _error_code, size_t _bytes_transferred) {
	if (_error_code != boost::system::errc::success) {
		SetWriting(false);
		return;
	}

	//send_buffers
	//send_buffers.
	//send_buffers
	//send_buffers.erase_begin

	if (0 == send_buffers.UsedSize()) {
		SetWriting(false);
		return;
	}

	boost::asio::async_write(
		GetSocket(),
		boost::asio::buffer(send_buffer),
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

