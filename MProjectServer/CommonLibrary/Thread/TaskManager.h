/*****************************************************************//**
 * \file   TaskManager.h
 * \brief  Coroutine task manager
 * 
 * \author dek0058
 * \date   2022-11-08
 *********************************************************************/
#pragma once

#include "GlobalDefine.h"
#include "Utility/TSingleton.h"


class TaskManager : public TSingleton<TaskManager> {
public:
	TaskManager();

	void Request(std::function<void()> _callback);
	void Execute();
	
private:
	
	std::vector<std::shared_ptr<struct FEvent>> events;

};
