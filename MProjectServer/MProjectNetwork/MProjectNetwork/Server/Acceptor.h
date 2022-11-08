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
#include <boost/asio/ip/tcp.hpp>

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
	Acceptor(int _fps, std::shared_ptr<MEngine> _server, ushort _port);
	
	
	

protected:
	
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnStop() override;
	
private:

	std::weak_ptr<MEngine> server;
	std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor;
	boost::asio::ip::tcp::endpoint endpoint;

	std::atomic_bool is_accepting = false;
};

}	// network
}	// mproject
