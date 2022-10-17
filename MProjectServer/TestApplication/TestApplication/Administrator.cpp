#include "Administrator.h"

#include "TestApplication/Manager/UIManager.h"
#include "TestApplication/Server/TestEngine.h"

#include "MProjectLogger/Logger/SpdLogger.h"

namespace mproject {

bool Administrator::Initialize() {

	
	server_port = 7778;

	engine = std::make_unique<TestEngine>(server_port);
	logger::SpdLogger log(FString(pTEXT("Administrator")), FString(pTEXT("./Logs")));

	StartUI();
	StartServer();
	
	//

	
	//auto frame = mproject::UIManager::GetMutableInstance().Create<mproject::ui::TestFrame>(nullptr);
	

	return true;
}

void Administrator::Finalize() {


}


void Administrator::StartUI() {
	UIManager::GetMutableInstance().Start();
}

void Administrator::StartServer() {

	//engine->Start();

}




}	// mproject

