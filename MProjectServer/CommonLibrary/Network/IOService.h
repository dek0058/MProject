#pragma once
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "NetworkDefine.h"
#include "Utility/SPSCQueue.h"

class NetworkServer;
struct FSession;
struct FPacket;

class IOService : public std::enable_shared_from_this<IOService> {
public:
	IOService(NetworkServer* _network_server);
	~IOService();


	virtual void Start(uint _thread_count);
	virtual void Stop();

	/// empty virtual func
	virtual bool Connect() { return false; }
	virtual void Loop() { ; }

	/// getter
	boost::asio::io_service& GetIOService() { return IO_service; }
	virtual ESessionType GetSessionType() const = 0;

	void PushSession(std::shared_ptr<FSession> _session);
	bool PopSession(std::shared_ptr<FSession>& _session);

	void PushNetEvent(ENetEventType _type, std::shared_ptr<FSession> _session);
	void ExecuteMessage(std::shared_ptr<FSession> _session, std::unique_ptr<FPacket> _packet);

protected:
	
	void StoreOwnerSesion(std::shared_ptr<FSession> _session);
	
	int GetTheradCount() const { return static_cast<int>(IO_thread_group.size()); }
	
protected:

	boost::asio::io_service IO_service;
	boost::asio::io_service::strand strand;
	boost::thread_group IO_thread_group;

	NetworkServer* network_server;

	std::vector<std::shared_ptr<FSession>> session_vector;
	SPSCQueue<std::shared_ptr<FSession>> session_queue;

	std::atomic<bool> is_stopped;

};

