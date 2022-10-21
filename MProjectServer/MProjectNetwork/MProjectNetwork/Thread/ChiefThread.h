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
namespace logger
{
class ILogger;
}	// logger

namespace network {

class EliteThread;

class ChiefThread : public MThread {

public:
	
	/**
	* \param _name Thread name
	* \param _fps Thread frames per second
	*/
	ChiefThread(FString _name, int _fps);

	~ChiefThread();

public:


protected:
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnStop() override;

	void AddSubThread(std::shared_ptr<EliteThread> _sub_thread);

protected:
	FString name;
	int fps;
	
	std::stop_source stop_source;
	std::vector<std::shared_ptr<EliteThread>> sub_threads;
	

	std::unique_ptr<logger::ILogger> logger;
};

}	// network
}	// mproject
