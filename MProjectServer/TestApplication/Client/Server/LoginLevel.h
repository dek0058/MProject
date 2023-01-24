#pragma once
#include "Client/ServerDefine.h"
#include "MProjectNetwork/Thread/EliteThread.h"
#include "MProjectNetwork/Core/Socket.h"

namespace mproject {

namespace network {
class Session;
}	// network

class TestEngine;

class LoginLevel : public network::EliteThread {
	using Header = network::FHeader;
public:

	LoginLevel(
		int _fps,
		std::shared_ptr<TestEngine> _server,
		ushort _port,
		boost::asio::io_service& _IO_service,
		size_t _session_count,
		size_t _receive_packet_capacity,
		size_t _max_packet_size,
		decimal _heartbeat_second
	);

protected:
	
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnStop() override;
	
	void OnReceive(network::Packet<Header> const& _packet, size_t _bytes_transferred, network::FPeer const& _peer);
	void OnConnection(network::FPeer const& _peer);
	void OnDisconnection(network::FPeer const& _peer);

private:
	
	std::shared_ptr<TestEngine> server;

	network::Socket<Header> socket;

	size_t session_count;
	std::vector<network::Session*> sessions;
	//std::unordered_set<network::UUID> peer_key_set;

	//SPSCQueue<network::Session*> session_queue;
};


}	// mproject