﻿/*****************************************************************//**
 * \file   Socket.h
 * \brief  reliable udp socket
 * 
 * \author dek0058
 * \date   2022-11-08
 *********************************************************************/
#pragma once
#include "MProjectNetwork/NetworkDefine.h"
#include "boost/asio.hpp"

namespace mproject {
namespace network {

class MEngine;

class Socket {
	
public:

	Socket(std::shared_ptr<MEngine> _server, boost::asio::ip::udp::endpoint _endpoint, size_t _recv_buffer_size);

private:

	void OnKeepAliveCheck();
	void OnKeepAlive();

private:

	bool listening;

	std::weak_ptr<MEngine> server;
	boost::asio::ip::udp::socket socket;
	boost::asio::ip::udp::endpoint remote_endpoint;
	boost::asio::deadline_timer timer;

	std::vector<byte> recv_buffer;

};

}	// network
}	// mproject
