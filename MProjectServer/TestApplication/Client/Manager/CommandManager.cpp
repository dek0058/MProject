#include "CommandManager.h"
#include "Thread/TaskManager.h"

#include "Client/Administrator.h"

#include "Client/Command/Command.h"
#include "Client/Command/CommandCaller.h"
#include "Client/Command/CommonCaller.h"
#include "Client/Command/ServerCaller.h"



namespace mproject {

CommandManager::CommandManager() {
	command_caller_map.reserve(100);
	
	CommonCaller::Initialize(this);
	ServerCaller::Initialize(this);
}

CommandManager::~CommandManager() {
	
}

void CommandManager::Execute(std::optional<FCommand> _command) {
	if (!_command) {
		return;
	}
	
	if (_command->command.Equals(pTEXT("?")))
	{
		_command->command = pTEXT("help");
	}
	
	if (!command_caller_map.contains(_command->command)) {
		return;
	}

	if (!command_caller_map[_command->command]) {
		return;
	}
	try {
		TaskManager::GetMutableInstance().Request([_command] {
			GetMutableInstance().GetCommandCaller(_command->command)->Execute(_command);
		});
	}
	catch (std::exception _exception) {
		Administrator::GetMutableInstance().WriteLog_Error(FString(_exception.what()));
	}
}

void CommandManager::ForEach(std::function<void(FString const&, std::shared_ptr<CommandCaller>)> _callback) const {
	for (auto& [key, value] : command_caller_map) {
		if (value != nullptr) {
			_callback(key, value);
		}
	}
}

}	// mproject
