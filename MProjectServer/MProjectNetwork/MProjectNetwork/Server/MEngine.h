/*****************************************************************//**
 * \file   MEngine.h
 * \brief  MEngine class
 * \details Server core management class
 * 
 * \author dek0058
 * \date   2022-10-31
 *********************************************************************/
#pragma once
#include "MProjectNetwork/NetworkDefine.h"
#include "MProjectNetwork/Thread/ChiefThread.h"
#include "Utility/MemoryPool.h"

namespace mproject {

namespace logger {
class ILogger;
}	// logger

namespace network {

class IOService;
class Session;
//class Acceptor;

class MEngine : public ChiefThread {
	using Logger = logger::ILogger;

public:
	
	/**
	 * \param int _fps Frames per second
	 */
	MEngine(
		FString _name,
		int _fps,
		std::shared_ptr<Logger> _logger,
		size_t _session_count,
		size_t _receive_packet_capacity,
		size_t _max_packet_size,
		decimal _heartbeat_second
	);

	~MEngine();

protected:
	
	virtual void OnPreStart() override;
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnStop() override;
	
public:
	std::shared_ptr<IOService> GetIOService() {
		return IO_service;
	}

/* Session ~ */
public:
	/** 메모리 풀에서 세션을 가져옵니다.*/
	Session* GetSession();

	/** 종료 된 세션을 반환합니다.*/
	void ReleaseSession(Session* _session);

	/** 연결 된 세션임을 결정합니다. */
	void ConnectSession(Session* _session);

	/** 세션이 연결이 종결 됬음을 알립니다. */
	void DisconnectSession(Session* _session);

protected:
	
	virtual void OnConnectSession(Session* _session) {}

private:
	SessionKey GetSessionKey() {
		SessionKey Result = 0;
		if (!recycle_session_key_queue.try_pop(Result)) {
			Result = ++origine_session_key;
		}
		return Result;
	}
	
	void ReleaseSessionKey(SessionKey _key) {
		recycle_session_key_queue.push(_key);
	}

/* Acceptor ~ */
//public:
//
//	/** Acceptor 초당 프레임을 설정합니다. */
//	void SetAcceptorFps(int _fps) {
//		acceptor_fps = _fps;
//	}
//
//	/** Acceptor 포트를 설정합니다. */
//	void SetAcceptorPort(ushort _port) {
//		acceptor_port = _port;
//	}
//	
//	/** Acceptor의 기본 정보를 세팅합니다. */
//	void SetAcceptorInfo(size_t _receive_packet_capacity, size_t _max_packet_size, decimal _heartbeat_second) {
//		acceptor_receive_packet_capacity = _receive_packet_capacity;
//		acceptor_max_packet_size = _max_packet_size;
//		acceptor_heartbeat_second = _heartbeat_second;
//	}

private:

	std::shared_ptr<IOService> IO_service;

	size_t receive_packet_capacity;
	size_t max_packet_size;
	decimal heartbeat_second;
	
	//! Session
	size_t session_count;
	std::atomic<SessionKey> origine_session_key;
	MemoryPool<Session> session_pool;
	hashmap<SessionKey, Session*> connect_session_map;
	concurrency::concurrent_queue<SessionKey> recycle_session_key_queue;

	// TODO:Thread

	//! Acceptor
	//int acceptor_fps;
	//ushort acceptor_port;
	//size_t acceptor_receive_packet_capacity;
	//size_t acceptor_max_packet_size;
	//decimal acceptor_heartbeat_second;
	//std::shared_ptr<Acceptor> acceptor;
};

}	// network
}	// mproject
