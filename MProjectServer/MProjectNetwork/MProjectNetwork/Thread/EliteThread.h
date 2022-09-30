/*****************************************************************//**
 * \file   EliteThread.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-09-30
 * \version 0.1
 *********************************************************************/

#pragma once
#include "Thread/MThread.h"

namespace mproject {
namespace network {

class ChiefThread;

class EliteThread : public MThread {

public:
	EliteThread(int _fps, std::weak_ptr<ChiefThread> _chief_thread);
	
private:

	std::weak_ptr<ChiefThread> chief_thread;

};

}	// network
}	// mproject
