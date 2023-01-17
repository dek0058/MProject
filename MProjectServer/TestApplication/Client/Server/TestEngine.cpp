#include "TestEngine.h"
#include "Client/ServerDefine.h"
#include "Client/Server/LoginLevel.h"
#include "MProjectLogger/Core/ILogger.h"
#include "MProjectNetwork/Core/IOService.h"

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
	
	/** 로그인 레벨 */
	, login_port(Default_Login_Port)
	, login_receive_packet_capacity(_receive_packet_capacity)
	, login_max_packet_size(_max_packet_size)
	, login_heartbeat_second(_heartbeat_second)

	/** 게임 레벨 */
	, game_port(Default_Game_Port)
{
	

}

void TestEngine::OnPreStart() {
	__super::OnPreStart();

	login_level = std::make_shared<LoginLevel>(
		fps,
		std::static_pointer_cast<TestEngine>(shared_from_this()),
		login_port,
		GetIOService()->Get(),
		login_receive_packet_capacity,
		login_max_packet_size,
		login_heartbeat_second
	);
	thread_count++;
		
	
}

void TestEngine::OnStart() {
	__super::OnStart();
	
	AddSubThread(login_level);
}

void TestEngine::OnUpdate() {
	__super::OnUpdate();
	
}

void TestEngine::OnStop() {
	__super::OnStop();

}

void TestEngine::OnConnectSession(Session* _session) {
	WriteLog_Info(pTEXT("Test Engine connect!"));



}

}	// mproject

