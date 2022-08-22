#pragma once

#include "NetworkDefine.h"

#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>

class IOService;
class Session;
class SessionObserver;

class Acceptor : public std::enable_shared_from_this<Acceptor>
{

public:

	Acceptor(std::shared_ptr<IOService> _IO_service, std::shared_ptr<SessionObserver> _session_observer, ushort _port_num, uint _thread_count);
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

	//! Management
	std::shared_ptr<SessionObserver> session_ob;

	uint thread_count;
};
