#include "HeadProtocolHandlerManager.h"
#include "Core/MLogger.h"

#pragma region Include_Protocol
#include "Protocol/TestProtocol.h"
#pragma endregion


void HeadProtocolHandlerManager::OnRegisterHandler() {
	MLogger::GetMutableInstance().LogError("Register Handler!");

	RegisterHandler(std::make_shared<TestProtocolHandler>());

}
