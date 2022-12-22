/*****************************************************************//**
 * \file   Socket.h
 * \brief  reliable udp socket
 * 
 * \author dek0058
 * \date   2022-11-09
 *********************************************************************/
#pragma once
#include <boost/asio.hpp>

#include "Peer.h"
#include "Packet.h"
#include "Utility/CircularBuffer.h"

namespace mproject {
namespace network {

class MEngine;
class IOService;

template<typename Header = FHeader>
	requires std::derived_from<Header, FHeader>
class Socket {
	using UDP_Scoket = boost::asio::ip::udp::socket;
	using UDP = boost::asio::ip::udp;
	using EndPoint = UDP::endpoint;

	template<typename... Types>
	using HandlerType = std::function<void(Types...)>;
	using ReceiveHandlerType = HandlerType<Packet<Header> const&, size_t, FPeer const&>;
	using ConnectionHandlerType = HandlerType<FPeer const&>;
	using DisconnectionHandlerType = HandlerType<FPeer const&>;
	using TimeoutHandlerType = HandlerType<FPeer const&>;

public:

	Socket(
		std::shared_ptr<MEngine> _server, 
		boost::asio::io_service& _IO_service,
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
	
	void AsyncSendTo(void* _buffer, size_t _buffer_size, EndPoint& _end_point) {
		if (socket) {
			socket->async_send_to(
				boost::asio::buffer(_buffer, _buffer_size),
				_end_point,
				boost::asio::bind_executor(
					strand.value(),
					[this](boost::system::error_code const& _error, size_t _bytes_transferred) {
						if (_error != boost::system::errc::success) {
							// TODO: 에러
						}
					}
				)
			);
		}
	}

	void AsyncSendToAll(void* _buffer, size_t _buffer_size) {
		for (auto& peer : peers) {
			AsyncSendTo(_buffer, _buffer_size, peer.endpoint);
		}
	}

	FPeer const& Self() const {
		return self;
	}

private:

	void Receive();
	void OnRecive(boost::system::error_code const& _error_code, size_t _bytes_transferred);

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
	std::optional<boost::asio::io_service::strand> strand;
	std::optional<EndPoint> remote_endpoint;
	std::optional<boost::asio::deadline_timer> timer;

	FPeer self;
	CircularBuffer_A sync_buffer;
	std::vector<byte> receive_buffer;
	std::list<FPeer> peers;

	ReceiveHandlerType receive_handler;
	ConnectionHandlerType connection_handler;
	DisconnectionHandlerType disconnection_handler;
	TimeoutHandlerType timeout_handler;

};

}	// network
}	// mproject
