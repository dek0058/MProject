#include "IOService.h"

#include <boost/asio.hpp>

namespace mproject {
namespace network {

IOService::IOService() 
	: work_guard(nullptr) {
}

IOService::~IOService() {
	work_guard = nullptr;
}

void IOService::Run() {
	if (nullptr != work_guard.get()) {
		work_guard.reset();
		data.restart();
	}
	work_guard = std::make_unique<boost::asio::executor_work_guard<boost::asio::io_service::executor_type>>(data.get_executor());
	data.run();
}

void IOService::Stop() {
	if (!data.stopped()) {
		data.stop();
	}
}

void IOService::RequestStop() {
	if (nullptr == work_guard.get()) {
		Stop();
		return;
	}
	work_guard->reset();
}

}	// network
}	// mproject
