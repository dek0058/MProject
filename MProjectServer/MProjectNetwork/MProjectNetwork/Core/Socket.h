/*****************************************************************//**
 * \file   Socket.h
 * \brief  reliable udp socket
 * 
 * \author dek0058
 * \date   2022-11-09
 *********************************************************************/
#pragma once
#include "MProjectNetwork/NetworkDefine.h"
#include <boost/asio.hpp>

#include "Peer.h"
#include "Utility/CircularBuffer.h"

namespace mproject {
namespace network {

class MEngine;
class IOService;

class Socket {
	using UDP_Scoket = boost::asio::ip::udp::socket;
	using UDP = boost::asio::ip::udp;
	using EndPoint = UDP::endpoint;

public:

	Socket(
		std::shared_ptr<MEngine> _server, 
		EndPoint _endpoint,
		size_t _receive_packet_capacity,
		size_t _max_packet_size,
		uint _heartbeat_second = 5);

public:

	void Open(UDP& _ip_protocol) {
		if (socket) {
			socket->open(_ip_protocol);
		}
	}

	void Close() noexcept;

	void Connect(EndPoint& _endpoint);

	void Bind(EndPoint& _end_point) noexcept {
		if (socket) {
			socket->bind(_end_point);
		}
	}

private:

	void Receive();
	void OnRecive();

	void OnHeartBeat();
	void HeartBeat();

private:

	size_t receive_packet_capacity;
	size_t max_packet_size;
	uint heartbeat_second;
	bool listening;

	std::weak_ptr<MEngine> server;
	std::weak_ptr<IOService> IO_service;

	std::optional<UDP_Scoket> socket;
	std::optional<EndPoint> remote_endpoint;
	std::optional<boost::asio::deadline_timer> timer;

	CircularBuffer_A sync_buffer;

};

}	// network
}	// mproject
