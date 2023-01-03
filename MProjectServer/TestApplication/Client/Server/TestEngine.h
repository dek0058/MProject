#pragma once
/*****************************************************************//**
 * \file   TestEngine.h
 * \brief  TestEngine class
 * \details Test Server Engine.
 * 
 * \author dek0058
 * \date   2022-09-16
 * \version 0.1
 *********************************************************************/

#include "MProjectNetwork/Server/MEngine.h"

namespace mproject {

namespace logger
{
class ILogger;
}	// logger

class TestEngine : public network::MEngine {
	using Logger = logger::ILogger;

public:
	TestEngine(
		std::shared_ptr<Logger> _logger,
		ushort _acceptor_port,
		size_t _session_count,
		size_t _receive_packet_capacity,
		size_t _max_packet_size,
		decimal _heartbeat_second
	);


private:


	

};

}
