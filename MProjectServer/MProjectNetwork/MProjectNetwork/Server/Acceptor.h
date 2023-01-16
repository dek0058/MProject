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
#include "Utility/SPSCQueue.h"

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
		ushort _port,
		boost::asio::io_service& _IO_service,
		size_t _max_session_count,
		size_t _receive_packet_capacity,
		size_t _max_packet_size,
		decimal _heartbeat_second
	);
	
protected:
	
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnStop() override;
	
private:
	void OnConnectionHandler(FPeer const& _peer);
	
private:

	std::shared_ptr<MEngine> server;
	
	Socket<Header> socket;
	SPSCQueue<Session*> session_queue;
};

}	// network
}	// mproject
