#include "HeadProtocolHandlerManager.h"
#include "Core/LogManager.h"

#pragma region Include_Protocol
#include "Protocol/ClientLoginProtocol.h"
#include "Protocol/ClientWorldProtocol.h"
#pragma endregion


void HeadProtocolHandlerManager::OnRegisterHandler() {
	LogManager::GetMutableInstance().GenericLog(ELogLevel::Info, "HeadProtocolHandlerManager", "OnRegisterHandler", "Register Handler!");
	
#pragma region Client Login

	RegisterHandler<NC2S_UserLoginHandlerHandler>();
	RegisterHandler<NS2C_UserLoginHandlerHandler>();

	RegisterHandler<NC2S_UserLogoutHandlerHandler>();
	RegisterHandler<NS2C_UserLogoutHandlerHandler>();

	
#pragma endregion
	
#pragma region Client World

	RegisterHandler<NC2S_JoinWorldHandlerHandler>();
	RegisterHandler<NS2C_JoinWorldHandlerHandler>();
	
	RegisterHandler<NC2S_LeftWorldHandlerHandler>();
	RegisterHandler<NS2C_LeftWorldHandlerHandler>();
	
	RegisterHandler<NS2C_JoinUserInWorldHandlerHandler>();
	RegisterHandler<NS2C_LeftUserInWorldHandlerHandler>();


#pragma endregion

	
#pragma region Client Actor

	
#pragma endregion

}
