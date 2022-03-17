#pragma once
#include <boost/asio.hpp>

using namespace boost;

class IOService {

public:
	IOService();

	asio::io_service& GetIOService() { return IO_service; }

private:

	asio::io_service IO_service;
};

