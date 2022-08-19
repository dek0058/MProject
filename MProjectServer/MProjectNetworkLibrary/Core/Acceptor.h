#pragma once

#include "NetworkDefine.h"

#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>

class IOService;
class Session;

class Acceptor : public std::enable_shared_from_this<Acceptor>
{

public:

	Acceptor(std::shared_ptr<IOService> _IO_service, ushort _port_num, uint _thread_count);
	~Acceptor();

public:
	void Start();
private:
	void OnStart();

private:
	void OnAccept();
	void PostAccept(std::shared_ptr<Session> _session, boost::system::error_code const& _ec);

private:

	//! Network
	std::shared_ptr<IOService> IO_service;
	boost::asio::ip::tcp::acceptor acceptor;
	boost::asio::io_service::strand strand;
	
	//! Thread
	boost::thread_group thread_group;
	uint thread_count;
};
