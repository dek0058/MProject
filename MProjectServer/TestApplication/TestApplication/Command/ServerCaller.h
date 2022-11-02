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

class ServerCaller {
	DELETE_REFERENCE_CREATOR(ServerCaller)
public:
	static void Initialize();
};


class CommandCaller_EngineStart final : public CommandCaller {
	
	
public:
	virtual bool Execute(std::optional<FCommand> _command) override;

};

}	// mproject
