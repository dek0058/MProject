/*****************************************************************//**
 * \file   Acceptor.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-10-04
 * \version 0.1
 *********************************************************************/

#pragma once
#include "MProjectNetwork/Thread/EliteThread.h"

namespace mproject {
namespace network {

class MEngine;
class IOService;
class Session;

class Acceptor : public EliteThread {
	
public:
	
	/**
	 * \param _fps		Frames per second
	 * \param _engine	Server engine.
	 */
	Acceptor(int _fps, std::shared_ptr<MEngine> _server);
	
	
	

protected:
	
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnStop() override;
	
private:

	std::weak_ptr<MEngine> server;
	
};

}	// network
}	// mproject
