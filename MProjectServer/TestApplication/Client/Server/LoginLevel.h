#pragma once
#include "Client/ServerDefine.h"
#include "MProjectNetwork/Thread/EliteThread.h"
#include "MProjectNetwork/Core/Socket.h"

namespace mproject {

class TestEngine;

class LoginLevel : public network::EliteThread {
	using Header = network::FHeader;

public:

	LoginLevel(
		int _fps,
		std::shared_ptr<TestEngine> _server,
		ushort _port,
		boost::asio::io_service& _IO_service,
		size_t _receive_packet_capacity,
		size_t _max_packet_size,
		decimal _heartbeat_second
	);

protected:
	
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnStop() override;
	
private:
	
	std::shared_ptr<TestEngine> server;

	network::Socket<Header> socket;

	
};


}	// mproject