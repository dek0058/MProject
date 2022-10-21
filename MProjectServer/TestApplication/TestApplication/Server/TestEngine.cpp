#include "TestEngine.h"

namespace mproject {

TestEngine::TestEngine(ushort _acceptor_port)
	: MEngine(FString(pTEXT("TestEngine")), 60, _acceptor_port) {


	
}

}	// mproject

