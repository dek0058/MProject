#include "IOService.h"


namespace mproject {
namespace network {

IOService::IOService() : is_stopped(true) {
	
}

IOService::~IOService() {
	Stop();
}

void IOService::Start() {
	if (true == IsRunning()) {
		return;
	}
	is_stopped.store(false);
	GetIOService().run();
}

void IOService::Stop() {
	if (false == IsRunning()) {
		return;
	}
	is_stopped.store(true);
	GetIOService().stop();
}


}	// network
}	// mproject
