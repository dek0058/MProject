/*****************************************************************//**
 * \file   CommandManager.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-11-01
 *********************************************************************/

#pragma once

#include "TestApplication/ServerDefine.h"
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
	void RegisterCommand(StringKey _key) {
		if (command_caller_map.contains(_key)) {
			throw std::exception("Already registered command.");
		}
		command_caller_map[_key] = std::make_optional<T>();
	}

	bool Execute(std::optional<FCommand> _command);
	
	
private:


private:

	hashmap<StringKey, std::optional<CommandCaller>> command_caller_map;

};

}	// mproject

