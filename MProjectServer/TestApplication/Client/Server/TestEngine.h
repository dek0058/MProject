#pragma once
/*****************************************************************//**
 * \file   TestEngine.h
 * \brief  TestEngine class
 * \details Test Server Engine.
 * 
 * \author dek0058
 * \date   2023-01-17
 *********************************************************************/

#include "MProjectNetwork/Server/MEngine.h"

namespace mproject {

class LoginLevel;

namespace logger {
class ILogger;
}	// logger

namespace network {
class Session;
}

class TestEngine : public network::MEngine {
	using Logger = logger::ILogger;
	using Session = network::Session;

public:
	TestEngine(
		std::shared_ptr<Logger> _logger,
		size_t _session_count,
		size_t _receive_packet_capacity,
		size_t _max_packet_size,
		decimal _heartbeat_second
	);

protected:

	virtual void OnPreStart() override;
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnStop() override;

	virtual void OnConnectSession(Session* _session) override;

private:

	ushort login_port;
	size_t login_receive_packet_capacity;
	size_t login_max_packet_size;
	decimal login_heartbeat_second;
	std::shared_ptr<LoginLevel> login_level;
	
	ushort game_port;

};

}
