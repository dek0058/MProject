/*****************************************************************//**
 * \file   CommonCaller.h
 * \brief  
 * 
 * \author dek0058
 * \date   2023-01-04
 *********************************************************************/
#pragma once
#include "CommandCaller.h"
#include "GuardDefine.h"

namespace mproject {

class CommandManager;

class CommonCaller {
	DELETE_REFERENCE_CREATOR(CommonCaller)
public:
	static void Initialize(CommandManager* _command_manager);

private:

	class Help final : public CommandCaller {
	public:
		virtual void Execute(std::optional<FCommand> _command) override;
		virtual FString help() override {
			return pTEXT("모든 명령어를 출력합니다.");
		}
	};
};




}	// mproject
