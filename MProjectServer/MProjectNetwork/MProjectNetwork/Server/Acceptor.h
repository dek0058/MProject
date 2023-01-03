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
#include "MProjectNetwork/Core/Socket.h"

namespace mproject {
namespace network {

class MEngine;
class IOService;
class Session;

class Acceptor : public EliteThread {
protected:
	using Header = FHeader;

public:
	
	/**
	 * \param _fps		Frames per second
	 * \param _engine	Server engine.
	 */
	Acceptor(
		int _fps,
		std::shared_ptr<MEngine> _server,
		ushort _port
	);
	
	
	

protected:
	
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnStop() override;
	
private:

	void OnReceiveHandler(Packet<Header> const& _packet, size_t _bytes_transferred, FPeer const& _peer);
	void OnConnectionHandler(FPeer const& _peer);
	void OnDisconnectionHandler(FPeer const& _peer);
	void OnTimeoutHandler(FPeer const& _peer);
	
private:

	std::shared_ptr<MEngine> server;
	
	std::unique_ptr<Socket<Header>> socket;
	EndPoint endpoint;
};

}	// network
}	// mproject
