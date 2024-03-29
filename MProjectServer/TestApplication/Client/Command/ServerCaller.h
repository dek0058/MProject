﻿/*****************************************************************//**
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
		virtual FString help() override {
			return
				pTEXT("서버 엔진을 시작하거나 종료합니다. 파라미터:[on/off]")
				pTEXT("\n")
				pTEXT("on:서버를 시작합니다.")
				pTEXT("\n")
				pTEXT("off:서버를 종료합니다.");
		}
	};
};




}	// mproject
