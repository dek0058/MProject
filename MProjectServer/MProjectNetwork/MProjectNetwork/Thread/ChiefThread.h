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
enum class ELogLevel : byte;
}	// logger

namespace network {

class EliteThread;

class ChiefThread : public MThread {
private:
	using Logger = logger::ILogger;
	
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
	ChiefThread(FString _name, int _fps, std::shared_ptr<Logger> _logger);

	~ChiefThread();

public:

	/**
	 * \brief 로그를 출력합니다.
	 */
	void WriteLog(logger::ELogLevel _level, FString _msg);
	void WriteLog_Trace(FString _msg);
	void WriteLog_Debug(FString _msg);
	void WriteLog_Info(FString _msg);
	void WriteLog_Warnining(FString _msg);
	void WriteLog_Error(FString _msg);
	void WriteLog_Criticial(FString _msg);

	std::shared_ptr<Logger> GetLogger() {
		return logger;
	}

protected:
	virtual void OnPreStart() override;
	virtual void OnStart() override;
	virtual void OnPostStart() override;
	virtual void OnUpdate() override;
	virtual void OnStop() override;

	void AddSubThread(std::shared_ptr<EliteThread> _sub_thread);

protected:
	FString name;
	int fps;
	
	std::stop_source stop_source;
	size_t thread_count;
	std::vector<std::shared_ptr<EliteThread>> sub_threads;
	
	std::shared_ptr<Logger> logger;
};

}	// network
}	// mproject
