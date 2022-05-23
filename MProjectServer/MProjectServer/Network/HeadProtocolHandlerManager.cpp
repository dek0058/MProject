#include "HeadProtocolHandlerManager.h"
#include "Core/MLogger.h"

#pragma region Include_Protocol
#include "Protocol/ClientLoginProtocol.h"
#pragma endregion


void HeadProtocolHandlerManager::OnRegisterHandler() {
	MLogger::GetMutableInstance().LogError("Register Handler!");
	
	
	RegisterHandler(std::make_shared<NC2S_UserLoginHandlerHandler>());
	RegisterHandler(std::make_shared<NS2C_UserLoginHandlerHandler>());
	

	/*RegisterHandler(std::make_shared<TestProtocolHandler>());
	RegisterHandler(std::make_shared<UserLoginProtocolHandler>());
	RegisterHandler(std::make_shared<IssuseUserKeyProtocolHandler>());*/

}
