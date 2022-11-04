/*****************************************************************//**
 * \file   MainProcess.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-10-31
 *********************************************************************/

#pragma once
#include "TestApplication/ServerDefine.h"
#include "Thread/MThread.h"



namespace mproject {

namespace logger
{
class ILogger;
}	// logger

class MainProcess : public MThread {
public:
	MainProcess(int _fps = 60);


public:

	
protected:
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnStop() override;

};

}	// mproject
