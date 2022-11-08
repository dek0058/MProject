#include "ServerCaller.h"
#include "CommandMacro.h"
#include "Client/Administrator.h"
#include "Client/Server/TestEngine.h"

namespace mproject {

void ServerCaller::Initialize(CommandManager* _command_manager) {
	ADD_COMMAND(_command_manager, Engine);
}


void ServerCaller::Engine::Execute(std::optional<FCommand> _command) {
	if (!_command) {
		return;
	}
	
	FString param = _command->Get(0);
	if (param.Empty()) {
		return;
	}

	StringAlgorithm::ToLower(param);
	if (param.Equals(pTEXT("on"))) {
		Administrator::GetMutableInstance().StartEngine();
	} else if (param.Equals(pTEXT("off"))) {
		if (auto engine = Administrator::GetMutableInstance().GetEngine(); false == engine.expired()) {
			engine.lock()->Stop();
		}
	} else {
		return;
	}
	return;
}

}	// mproject
