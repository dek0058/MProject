/*****************************************************************//**
 * \file   ChiefThread.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-10-28
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

	/**
	 * \param _name Thread name
	 * \param _fps Thread frames per second
	 * \param _logger parent logger
	 */
	ChiefThread(FString _name, int _fps, std::shared_ptr<logger::ILogger> _logger);

	~ChiefThread();

public:

	std::shared_ptr<logger::ILogger> GetLogger() {
		return logger;
	}

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
	

	std::shared_ptr<logger::ILogger> logger;
};

}	// network
}	// mproject
