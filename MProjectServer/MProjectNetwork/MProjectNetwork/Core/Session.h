/*****************************************************************//**
 * \file   Session.h
 * \brief
 *
 * \author dek0058
 * \date   2022-10-08
 *********************************************************************/

#pragma once
#include "Socket.h"

namespace mproject {
namespace network {

class IOService;

class Session : std::enable_shared_from_this<Session> {
protected:
	using Header = FHeader;

public:
	Session(
		SessionKey _key,
		boost::asio::io_service& _IO_service,
		EndPoint _endpoint,
		size_t _receive_packet_capacity,
		size_t _max_packet_size,
		decimal _heartbeat_second
	);
	
	Session(
		SessionKey _key,
		boost::asio::io_service& _IO_service,
		size_t _receive_packet_capacity,
		size_t _max_packet_size,
		decimal _heartbeat_second
	);


public:

	/** set address */
	void SetAddress(Address _address) {
		address = _address;
	}

	SessionKey GetSessionKey() const {
		return session_key;
	}


private:

	void BindHandler();
	
	void OnReceiveHandler(Packet<Header> const& _packet, size_t _bytes_transferred, FPeer const& _peer);
	void OnConnectionHandler(FPeer const& _peer);
	void OnDisconnectionHandler(FPeer const& _peer);
	void OnTimeoutHandler(FPeer const& _peer);

private:

	SessionKey session_key;
	Address address;

	Socket<Header> socket;

};

}	// network
}	// mproject
