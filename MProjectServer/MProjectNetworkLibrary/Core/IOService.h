#pragma once

#include "NetworkDefine.h"

#include <boost/asio.hpp>

class Session;

class IOService : public std::enable_shared_from_this<IOService> {
	
public:
	IOService();
	~IOService();


	virtual std::shared_ptr<Session> GetSession() { 
		return nullptr;
	}
	
	virtual void Run() {
		IO_service.run();
	}

	boost::asio::io_service& GetIOService() {
		return IO_service;
	}
	
private:

	boost::asio::io_service IO_service;
};
