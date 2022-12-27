/*****************************************************************//**
 * \file   Session.h
 * \brief
 *
 * \author dek0058
 * \date   2022-10-08
 *********************************************************************/

#pragma once
#include "MProjectNetwork/NetworkDefine.h"
#include "Socket.h"

#include <boost/asio.hpp>

namespace mproject {
namespace network {


class Session : std::enable_shared_from_this<Session> {
protected:
	using Header = FHeader;

public:
	Session();

private:

	void OnReceiveHandler(Packet<Header> const& _packet, size_t _bytes_transferred, FPeer const& _peer);
	void OnConnectionHandler(FPeer const& _peer);
	void OnDisconnectionHandler(FPeer const& _peer);
	void OnTimeoutHandler(FPeer const& _peer);

private:

	SessionKey session_key;

	std::optional<Socket<Header>> socket;

};

}	// network
}	// mproject
