#include "TestEngine.h"
#include "MProjectLogger/Core/ILogger.h"

namespace mproject {

TestEngine::TestEngine(
	std::shared_ptr<logger::ILogger> _logger,
	ushort _acceptor_port,
	size_t _session_count,
	size_t _receive_packet_capacity,
	size_t _max_packet_size
	)
	: MEngine(
		FString(pTEXT("TestEngine")),
		60,
		_logger,
		_acceptor_port,
		_session_count,
		_receive_packet_capacity,
		_max_packet_size) {


	
}

}	// mproject

