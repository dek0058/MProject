/*****************************************************************//**
 * \file   CommandManager.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-11-01
 *********************************************************************/

#pragma once

#include "Client/ServerDefine.h"
#include "Utility/TSingleton.h"

namespace mproject {

struct FCommand;
class CommandCaller;

class CommandManager : public TSingleton<CommandManager> {
	

public:
	CommandManager();
	~CommandManager();

public:
	
	template<typename T>
		requires std::derived_from<T, CommandCaller>
	void RegisterCommand(FString _command) {
		if (command_caller_map.contains(_command)) {
			throw std::exception("Already registered command.");
		}
		command_caller_map[_command] = std::make_shared<T>();
	}

	void Execute(std::optional<FCommand> _command);
	
	std::shared_ptr<CommandCaller> GetCommandCaller(FString _command) {
		if (command_caller_map.contains(_command)) {
			return command_caller_map[_command];
		}
		return nullptr;
	}

	void ForEach(std::function<void(FString const&, std::shared_ptr<CommandCaller>)> _callback) const;

private:

	hashmap<FString, std::shared_ptr<CommandCaller>> command_caller_map;

};

}	// mproject

