#include "Administrator.h"

#include "Client/Manager/UIManager.h"
#include "Client/Core/MainProcess.h"
#include "Client/Server/TestEngine.h"

#include "MProjectLogger/Logger/SpdLogger.h"

#include "MProjectNetwork/Core/Socket.h"
#include "MProjectNetwork/Core/IOService.h"

namespace mproject {

using ELogLevel = logger::ELogLevel;

using namespace network;

bool Administrator::Initialize() {

	server_port = 7778;
	
	logger = std::make_shared<logger::SpdLogger>(FString(pTEXT("TestApplication")), FString(pTEXT("./Logs/Administrator.log")));

	main_process = std::make_shared<MainProcess>();
	engine = std::make_shared<TestEngine>(logger, server_port, 1024, 10000, 10000, 5);


	// UIManager 초기화 및 Main Form 생성
	UIManager::GetMutableInstance().Start();
	
	// 메인 스레드 시작
	main_process->Start(stop_source.get_token());

	StartEngine();

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

void Administrator::WriteLog(logger::ELogLevel _level, FString _msg) {
	if (nullptr != logger) {
		logger->WriteLog(_level, _msg);
	}
}

void Administrator::WriteLog_Trace(FString _msg) {
	WriteLog(ELogLevel::Trace, _msg);
}

void Administrator::WriteLog_Debug(FString _msg) {
	WriteLog(ELogLevel::Debug, _msg);
}

void Administrator::WriteLog_Info(FString _msg) {
	WriteLog(ELogLevel::Info, _msg);
}

void Administrator::WriteLog_Warnining(FString _msg) {
	WriteLog(ELogLevel::Warning, _msg);
}

void Administrator::WriteLog_Error(FString _msg) {
	WriteLog(ELogLevel::Error, _msg);
}

void Administrator::WriteLog_Criticial(FString _msg) {
	WriteLog(ELogLevel::Critical, _msg);
}

}	// mproject

