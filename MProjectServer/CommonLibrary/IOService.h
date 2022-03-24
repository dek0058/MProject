#pragma once
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "NetworkDefine.h"
#include "SPSCQueue.h"

using namespace boost;

class NetworkServer;
struct FSession;

class IOService {
public:
	IOService(std::shared_ptr<NetworkServer> _network_server);
	~IOService();


	virtual void Start(uint _thread_count);
	virtual void Stop();


	/// empty virtual func
	virtual bool Connect() { return false; }
	virtual void Loop() { ; }

	/// getter
	asio::io_service& GetIOService() { return IO_service; }
	virtual ESessionType GetSessionType() const = 0;

protected:
	int GetTheradCount() const { return static_cast<int>(IO_thread_group.size()); }

protected:

	asio::io_service IO_service;
	std::shared_ptr<NetworkServer> network_server;
	thread_group IO_thread_group;

	std::list<std::shared_ptr<FSession>> session_vector;
	SPSCQueue<std::shared_ptr<FSession>> session_queue;

	std::atomic<bool> is_stopped;

};

