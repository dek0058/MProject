#include "HeadProtocolHandlerManager.h"
#include "Core/LogManager.h"

#pragma region Include_Protocol
#include "Protocol/ClientLoginProtocol.h"
#include "Protocol/ClientWorldProtocol.h"
#include "Protocol/ClientActorProtocol.h"
#pragma endregion


void HeadProtocolHandlerManager::OnRegisterHandler() {
	LogManager::GetMutableInstance().GenericLog(ELogLevel::Info, "HeadProtocolHandlerManager", "OnRegisterHandler", "Register Handler!");
	
#pragma region Client Login

	RegisterHandler<NC2S_UserLoginProtocolHandler>();
	RegisterHandler<NS2C_UserLoginProtocolHandler>();

	RegisterHandler<NC2S_UserLogoutProtocolHandler>();
	RegisterHandler<NNS2C_UserLogoutProtocolHandler>();

	
#pragma endregion
	
#pragma region Client World

	RegisterHandler<NC2S_JoinWorldProtocolHandler>();
	RegisterHandler<NS2C_JoinWorldProtocolHandler>();
	
	RegisterHandler<NC2S_LeftWorldProtocolHandler>();
	RegisterHandler<NS2C_LeftWorldProtocolHandler>();
	
	RegisterHandler<NS2C_JoinUserInWorlddProtocolHandler>();
	RegisterHandler<NS2C_LeftUserInWorldProtocolHandler>();


#pragma endregion

	
#pragma region Client Actor

	RegisterHandler<NC2S_MoveActorInWorldProtocolHandler>();
	RegisterHandler<NS2C_MoveActorInWorldProtocolHandler>();
	
#pragma endregion

}
