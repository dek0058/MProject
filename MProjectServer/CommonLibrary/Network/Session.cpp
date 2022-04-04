#include "Session.h"
#include "MProjectServerDefine.h"

#include "IOService.h"

FSession::FSession(shared_ptr<IOService> _IO_service, ESessionType _session_type)
	: sock(_IO_service->GetIOService()), strand(_IO_service->GetIOService()), 
		session_key(0), session_type(_session_type), sequence_type(ESequenceType::Disconnected) {

}

FSession::~FSession() {
	system::error_code error_code;
	sock.close(error_code);
}
