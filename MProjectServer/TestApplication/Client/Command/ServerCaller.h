/*****************************************************************//**
 * \file   ServerCaller.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-11-02
 *********************************************************************/
#pragma once
#include "CommandCaller.h"
#include "GuardDefine.h"

namespace mproject {

class CommandManager;

class ServerCaller {
	DELETE_REFERENCE_CREATOR(ServerCaller)
public:
	static void Initialize(CommandManager* _command_manager);

private:

	class Engine final : public CommandCaller {
	public:
		virtual void Execute(std::optional<FCommand> _command) override;
	};
};




}	// mproject
