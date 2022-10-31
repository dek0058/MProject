/*****************************************************************//**
 * \file   MEngine.h
 * \brief  MEngine class
 * \details Server core management class
 * 
 * \author dek0058
 * \date   2022-10-31
 *********************************************************************/
#pragma once
#include "MProjectNetwork/Thread/ChiefThread.h"


namespace mproject {

namespace logger {
class ILogger;
}	// logger

namespace network {

class IOService;
class Session;
class Acceptor;

class MEngine : public ChiefThread {

public:
	
	/**
	 * \param int _fps Frames per second
	 */
	MEngine(FString _name, int _fps, ushort _acceptor_port, std::shared_ptr<logger::ILogger> _logger);

	~MEngine();

public:

	std::weak_ptr<IOService> GetIOService() {
		return IO_service;
	}

protected:
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnStop() override;
	
	
	

private:

	std::shared_ptr<IOService> IO_service;
	ushort acceptor_port;

	std::shared_ptr<Acceptor> acceptor;
};

}	// network
}	// mproject
