#pragma once

#include "NetworkDefine.h"

#include <boost/asio.hpp>


class IOService : public std::enable_shared_from_this<IOService> {
	
public:
	IOService();
	~IOService();
	
	virtual void Run() {
		IO_service.run();
	}

	boost::asio::io_service& GetIOService() {
		return IO_service;
	}
	
private:

	boost::asio::io_service IO_service;
};
