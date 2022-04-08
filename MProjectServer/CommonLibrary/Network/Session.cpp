#include "Session.h"
#include "MProjectServerDefine.h"

#include "IOService.h"

FSession::FSession(shared_ptr<IOService> _IO_service, ESessionType _session_type, size_t _send_buffer_size, size_t _recv_buffer_size)
	: sock(_IO_service->GetIOService()), strand(_IO_service->GetIOService()), 
		session_key(0), session_type(_session_type), sequence_type(ESequenceType::Disconnected) ,
		send_buffers(_send_buffer_size), recv_buffers(_recv_buffer_size) {

}

FSession::~FSession() {
	system::error_code error_code;
	sock.close(error_code);
}

void FSession::Accept(SessionKey _session_key) {
	session_key = _session_key;
	sequence_type = ESequenceType::Connected;
	send_buffers.clear();
	recv_buffers.clear();
}

void FSession::Connect()
{
}

void FSession::Disconnect()
{
}
