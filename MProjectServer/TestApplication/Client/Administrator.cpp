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

std::vector<byte> test_buffer(1024);
boost::asio::io_service test_io_serivce;
std::vector<std::thread> test_thread_pool;

UDP::socket sock(test_io_serivce);

bool Administrator::Initialize() {

	server_port = 7778;
	
	logger = std::make_shared<logger::SpdLogger>(FString(pTEXT("TestApplication")), FString(pTEXT("./Logs/Administrator.log")));

	main_process = std::make_shared<MainProcess>();
	engine = std::make_shared<TestEngine>(logger, server_port, 1024, 10000, 10000, 5);


	// UIManager 초기화 및 Main Form 생성
	UIManager::GetMutableInstance().Start();
	
	// 메인 스레드 시작
	main_process->Start(stop_source.get_token());
	
	//EndPoint endpoint(UDP::v4(), server_port);

	//sock.open(endpoint.protocol());
	//sock.bind(endpoint);
	//sock.async_receive_from(
	//	boost::asio::buffer(test_buffer),
	//	endpoint,
	//	[this](boost::system::error_code const& _error_code, size_t _bytes_transferred) {
	//		if (_error_code) {
	//			FString msg = FString(_error_code.message(), 0);
	//			WriteLog_Info(msg);
	//		}
	//		else {
	//			WriteLog_Info( FString(pTEXT("Received bytes")));
	//		}
	//	}
	//);

	////Socket<FHeader> sock(engine->GetIOService()->Get(), endpoint, 1024, 1024, 5);
	////sock.Start();

	//test_thread_pool.emplace_back([]() {
	//	test_io_serivce.run();
	//});

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

