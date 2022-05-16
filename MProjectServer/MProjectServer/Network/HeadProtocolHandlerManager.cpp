#include "HeadProtocolHandlerManager.h"
#include "Core/MLogger.h"

#pragma region Include_Protocol
#include "Protocol/TestProtocol.h"
#include "Protocol/UserLoginProtocol.h"
#include "Protocol/IssuseUserKeyProtocol.h"
#pragma endregion


void HeadProtocolHandlerManager::OnRegisterHandler() {
	MLogger::GetMutableInstance().LogError("Register Handler!");

	RegisterHandler(std::make_shared<TestProtocolHandler>());
	RegisterHandler(std::make_shared<UserLoginProtocolHandler>());
	RegisterHandler(std::make_shared<IssuseUserKeyProtocolHandler>());

}
