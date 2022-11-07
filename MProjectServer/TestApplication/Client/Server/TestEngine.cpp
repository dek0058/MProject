#include "TestEngine.h"
#include "MProjectLogger/Core/ILogger.h"

namespace mproject {

TestEngine::TestEngine(ushort _acceptor_port, std::shared_ptr<logger::ILogger> _logger)
	: MEngine(FString(pTEXT("TestEngine")), 60, _acceptor_port, _logger) {


	
}

}	// mproject

