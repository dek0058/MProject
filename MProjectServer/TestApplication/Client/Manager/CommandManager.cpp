#include "CommandManager.h"
#include "Client/Command/Command.h"
#include "Client/Command/CommandCaller.h"
#include "Client/Command/ServerCaller.h"

namespace mproject {



CommandManager::CommandManager() {

	ServerCaller::Initialize(this);

}

CommandManager::~CommandManager() {
	
}

bool CommandManager::Execute(std::optional<FCommand> _command) {
	if (!_command) {
		return false;
	}

	if (!command_caller_map.contains(_command->key)) {
		return false;
	}

	if (!command_caller_map[_command->key]) {
		return false;
	}

	return command_caller_map[_command->key]->Execute(_command);
}

}	// mproject
