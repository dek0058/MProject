/*****************************************************************//**
 * \file   CommandCaller.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-11-01
 *********************************************************************/
#pragma once

#include "Command.h"

namespace mproject {

class CommandCaller {
public:
	CommandCaller() = default;
	virtual ~CommandCaller() = default;

public:
	
	virtual bool Execute(std::optional<FCommand> _command) { return false; }
};

};	// mproject
