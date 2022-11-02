#include "CommandManager.h"
#include "TestApplication/Command/Command.h"
#include "TestApplication/Command/CommandCaller.h"
#include "TestApplication/Command/ServerCaller.h"

namespace mproject {



CommandManager::CommandManager() {

	ServerCaller::Initialize();

}

CommandManager::~CommandManager() {
	
}

bool CommandManager::Execute(std::optional<FCommand> _command) {
	if (!_command) {
		return false;
	}

	size_t key = _command->ToKey();
	if (!command_caller_map.contains(key)) {
		return false;
	}

	if (!command_caller_map[key]) {
		return false;
	}

	return command_caller_map[key]->Execute(_command);
}

}	// mproject
