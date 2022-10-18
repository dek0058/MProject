/*****************************************************************//**
 * \file   MainProcess.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-10-18
 *********************************************************************/

#pragma once
#include "TestApplication/ServerDefine.h"
#include "Thread/MThread.h"

namespace mproject {

class MainProcess : public MThread {
public:
	MainProcess(int _fps = 60);

};

}	// mproject
