#include "Administrator.h"

#include "TestApplication/Manager/UIManager.h"
#include "TestApplication/Core/MainProcess.h"
#include "TestApplication/Server/TestEngine.h"

#include "MProjectLogger/Logger/SpdLogger.h"

namespace mproject {

bool Administrator::Initialize() {

	// UIManager 초기화 및 Main Form 생성
	UIManager::GetMutableInstance().Start();

	main_process = std::make_shared<MainProcess>();

	server_port = 7778;

	engine = std::make_shared<TestEngine>(server_port);
	logger::SpdLogger log(FString(pTEXT("Administrator")), FString(pTEXT("./Logs")));

	main_process->Start(stop_source.get_token());

	
	return true;
}

int Administrator::Finalize() {

	// 스레드 중단 요청
	stop_source.request_stop();

	return 0;
}

void Administrator::StartEngine() {
	engine->Start(stop_source.get_token());
}

}	// mproject

