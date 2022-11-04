﻿#include "ServerCaller.h"
#include "CommandMacro.h"
#include "TestApplication/Administrator.h"
#include "TestApplication/Server/TestEngine.h"

namespace mproject {

void ServerCaller::Initialize(CommandManager* _command_manager) {
	ADD_COMMAND(_command_manager, Engine);
}


bool ServerCaller::Engine::Execute(std::optional<FCommand> _command) {
	if (!_command) {
		return false;
	}
	
	FString param = _command->Get(0);
	if (param.Empty()) {
		return false;
	}

	StringAlgorithm::ToLower(param);
	if (param.Equals(pTEXT("on"))) {
		Administrator::GetMutableInstance().StartEngine();
	} else if (param.Equals(pTEXT("off"))) {
		if (auto engine = Administrator::GetMutableInstance().GetEngine(); false == engine.expired()) {
			engine.lock()->Stop();
		}
	} else {
		return false;
	}
	return true;
}

}	// mproject
