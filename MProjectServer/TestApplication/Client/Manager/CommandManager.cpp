#include "CommandManager.h"
#include "Thread/TaskManager.h"

#include "MProjectLogger/Core/ILogger.h"

#include "Client/Administrator.h"

#include "Client/Command/Command.h"
#include "Client/Command/CommandCaller.h"
#include "Client/Command/ServerCaller.h"



namespace mproject {



CommandManager::CommandManager() {
	command_caller_map.reserve(100);
	
	ServerCaller::Initialize(this);
}

CommandManager::~CommandManager() {
	
}

void CommandManager::Execute(std::optional<FCommand> _command) {
	if (!_command) {
		return;
	}

	if (!command_caller_map.contains(_command->key)) {
		return;
	}

	if (!command_caller_map[_command->key]) {
		return;
	}
	try {
		TaskManager::GetMutableInstance().Request([_command] {
			GetMutableInstance().GetCommandCaller(_command->key)->Execute(_command);
		});
	}
	catch (std::exception const& _exception) {
		Administrator::GetMutableInstance().GetLogger().lock()->WriteLog(logger::ELogLevel::Error, FString(_exception.what()));
	}
}

}	// mproject
