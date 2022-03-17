#pragma once
#include <boost/asio.hpp>

#include "NetworkDefine.h"

using namespace boost;

class IOService;

class IOAcceptor {

public:

	IOAcceptor(shared_ptr<IOService> _IO_service);
	~IOAcceptor();

	void Start(const FAcceptInfo& _accept_info);
	void Stop();

private:

	FAcceptInfo accept_info;
	asio::io_service& io_service;
	std::shared_ptr<asio::ip::tcp::acceptor> acceptor;

};
