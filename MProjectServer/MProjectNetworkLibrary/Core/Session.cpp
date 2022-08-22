#include "Session.h"

#include "IOService.h"


Session::Session(std::shared_ptr<IOService> _IO_service, ESessionType _session_type, size_t _sb_size, size_t _rb_size) 
	: IO_service(_IO_service),
	  sock(IO_service->GetIOService()),
	  strand(IO_service->GetIOService()),
	  session_type(_session_type) {
	
}

Session::~Session() {
	sock.close();
}


