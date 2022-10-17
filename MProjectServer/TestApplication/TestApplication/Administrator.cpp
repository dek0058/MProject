#include "Administrator.h"

#include "TestApplication/Server/TestEngine.h"

namespace mproject {

bool Administrator::Initialize() {

	
	server_port = 7778;


	
	engine = std::make_unique<TestEngine>(server_port);

	
	return true;
}

void Administrator::StartServer() {

	engine->Start();

}

void Administrator::Finalize() {


}


}	// mproject

