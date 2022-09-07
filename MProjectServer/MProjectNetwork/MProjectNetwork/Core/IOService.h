#pragma once

//! library
#include <boost/asio/io_service.hpp>

#include "MProjectNetwork/NetworkDefine.h"

namespace mproject {
namespace network {

class IOService : public std::enable_shared_from_this<IOService> {
	
public:
	IOService();
	~IOService();

public:
	virtual void Start();
	virtual void Stop();

	//! Getter
	boost::asio::io_service& GetIOService() {
		return IO_service;
	}

	bool IsRunning() const {
		return !is_stopped.load();
	}

protected:


private:
	boost::asio::io_service IO_service;
	std::atomic<bool> is_stopped;
};

}	// network
}	// mproject
