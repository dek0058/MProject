#pragma once

#include "NetworkDefine.h"
#include "Utility/SPSCQueue.h"
#include "ProtocolHandler.h"

class IOService;
class IOAcceptor;
class IOConnector;
struct FNetEvent;
struct FSession;

class NetworkServer : public std::enable_shared_from_this<NetworkServer> {
	friend class IOAcceptor;
	friend class IOConnector;

	using SessionMMap = std::multimap<std::wstring, std::shared_ptr<FSession>>;

public:
	NetworkServer(std::unique_ptr<ProtocolHandlerManager> _handler_manager);
	~NetworkServer();

	void Start(std::vector<FAcceptInfo> _accept_info_vector, std::vector<FConnectInfo> _connect_info_vector);
	void Stop();
	void Loop();
	bool Connect(ESessionType _session_type);
	
	virtual void OnAccept(std::shared_ptr<FSession> _session);
	virtual void OnConnect(std::shared_ptr<FSession> _session);
	virtual void OnDissconnect(std::shared_ptr<FSession> _session);

	void RegisterAcceptor(FAcceptInfo const& _accept_info);
	void RegisterConnector(FConnectInfo const& _connect_info);

	void PushNetEvent(ENetEventType _type, std::shared_ptr<IOService> _IO_service, std::shared_ptr<FSession> _session);

	
	
private:

	static SessionKey AddSessionKey() {
		static SessionKey session_key = 0;
		return ++session_key;
	}

private:
	std::vector<std::unique_ptr<IOService>> IO_service_vector;
	std::unique_ptr<ProtocolHandlerManager> protocol_handler_manager;

	SPSCQueue<std::shared_ptr<FNetEvent>> net_event_queue;
	std::queue<std::shared_ptr<FNetEvent>> wait_net_event_queue;

	std::map<SessionKey, std::shared_ptr<FSession>> connected_session_map;
	SessionMMap connected_server_map;
};

