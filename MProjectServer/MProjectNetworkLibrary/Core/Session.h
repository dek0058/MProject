#pragma once

#include "NetworkDefine.h"

#include <boost/asio.hpp>

class IOService;

class Session : public std::enable_shared_from_this<Session> {


public:

	Session(std::shared_ptr<IOService> _IO_service, ESessionType _session_type, size_t _sb_size, size_t _rb_size);
	~Session();

	boost::asio::ip::tcp::socket& GetSocket() {
		return sock;
	}

protected:

	//! Network
	std::shared_ptr<IOService> IO_service;
	boost::asio::ip::tcp::socket sock;
	boost::asio::io_service::strand strand;

	//! Network Infromation
	ESessionType session_type;

	
};
