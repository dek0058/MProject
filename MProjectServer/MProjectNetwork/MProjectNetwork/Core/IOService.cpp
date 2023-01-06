#include "IOService.h"

#include <boost/asio.hpp>

namespace mproject {
namespace network {

IOService::IOService() {
}

IOService::~IOService() {
}

void IOService::Run() {
	IO_thread_group.emplace_back(
		[this](std::stop_token stop_token) {
			data.run();
		},
		stop_source.get_token()
	);
}

void IOService::Stop() {
	data.stop();
	stop_source.request_stop();
	for (auto& thread : IO_thread_group) {
		thread.join();
	}
	IO_thread_group.clear();

	stop_source = std::stop_source();
}

void IOService::RequestStop() {
	Stop();
}

}	// network
}	// mproject
