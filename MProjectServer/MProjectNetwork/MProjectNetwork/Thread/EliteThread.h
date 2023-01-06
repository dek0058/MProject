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

	/**
	 * \param _fps Frames per second
	 * \param _chief_thread	Chief thread
	 */
	EliteThread(int _fps, std::shared_ptr<ChiefThread> _chief_thread);
	
protected:
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnStop() override;

protected:
	std::shared_ptr<ChiefThread> GetChief() {
		return chief_thread.expired() ? nullptr : chief_thread.lock();
	}

private:

	std::weak_ptr<ChiefThread> chief_thread;

};

}	// network
}	// mproject
