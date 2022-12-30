#include "Administrator.h"

#include "Client/Manager/UIManager.h"
#include "Client/Core/MainProcess.h"
#include "Client/Server/TestEngine.h"

#include "MProjectLogger/Logger/SpdLogger.h"

namespace mproject {

bool Administrator::Initialize() {

	server_port = 7778;
	
	logger = std::make_shared<logger::SpdLogger>(FString(pTEXT("TestApplication")), FString(pTEXT("./Logs/Administrator.log")));

	main_process = std::make_shared<MainProcess>();
	engine = std::make_shared<TestEngine>(logger, server_port, 1024, 10000, 10000);


	// UIManager 초기화 및 Main Form 생성
	UIManager::GetMutableInstance().Start();
	
	// 메인 스레드 시작
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

