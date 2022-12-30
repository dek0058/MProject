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
#include "Utility/MemoryPool.h"

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
	MEngine(
		FString _name,
		int _fps,
		std::shared_ptr<logger::ILogger> _logger,
		ushort _acceptor_port,
		size_t _session_count,
		size_t _receive_packet_capacity,
		size_t _max_packet_size
	);

	~MEngine();

protected:
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnStop() override;
	
public:

	/** 메모리 풀에서 세션을 가져옵니다.*/
	Session* GetSession();

	/** 종료 된 세션을 반환합니다.*/
	void ReleaseSession(Session* _session);

	std::shared_ptr<IOService> GetIOService() {
		return IO_service;
	}
	

private:

	std::shared_ptr<IOService> IO_service;
	ushort acceptor_port;

	MemoryPool<Session> session_pool;
	size_t receive_packet_capacity;
	size_t max_packet_size;
	
	// TODO:Thread
	
	std::shared_ptr<Acceptor> acceptor;
};

}	// network
}	// mproject
