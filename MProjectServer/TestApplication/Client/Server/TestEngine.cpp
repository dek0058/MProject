#include "TestEngine.h"
#include "MProjectLogger/Core/ILogger.h"

namespace mproject {

TestEngine::TestEngine(
	std::shared_ptr<Logger> _logger,
	size_t _session_count,
	size_t _receive_packet_capacity,
	size_t _max_packet_size,
	decimal _heartbeat_second
)
	: MEngine(
		FString(pTEXT("TestEngine")),
		60,
		_logger,
		_session_count,
		_receive_packet_capacity,
		_max_packet_size,
		_heartbeat_second
	)
{
	
}

}	// mproject

