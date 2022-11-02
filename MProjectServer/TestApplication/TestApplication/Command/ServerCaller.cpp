#include "ServerCaller.h"
#include "TestApplication/Manager/CommandManager.h"

namespace mproject {

void ServerCaller::Initialize() {
	
	CommandManager::GetMutableInstance().RegisterCommand<CommandCaller_EngineStart>(pTEXT("EngineStart"));


}


bool CommandCaller_EngineStart::Execute(std::optional<FCommand> _command) {

	

	return true;
}

}	// mproject
