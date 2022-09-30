/*****************************************************************//**
 * \file   ChiefThread.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-09-30
 * \version 0.1
 *********************************************************************/

#pragma once
#include "Thread/MThread.h"
#include <barrier>

namespace mproject {
namespace network {

class EliteThread;

class ChiefThread : public MThread {

public:
	
	/**
	 * \param int _fps Frames per second
	 * \param size_t _sub_thread_count Sub thread count
	 */
	ChiefThread(int _fps, size_t _sub_thread_count);

protected:
	virtual void OnStart() override;
	virtual void OnUpdate() final override;
	virtual void OnStop() override;

private:

	std::vector<std::shared_ptr<EliteThread>> sub_threads;
};

}	// network
}	// mproject
