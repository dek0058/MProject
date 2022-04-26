#pragma once

#include "NetworkDefine.h"
#include "Utility/SPSCQueue.h"
#include "ProtocolHandler.h"

class IOService;
class IOAcceptor;
class IOConnector;
struct FNetEvent;
struct FSession;
struct FBaseProtocol;

class NetworkServer {
	friend class IOAcceptor;
	friend class IOConnector;

	using SessionMMap = std::multimap<std::wstring, std::shared_ptr<FSession>>;

public:
	NetworkServer(std::shared_ptr<ProtocolHandlerManager> _handler_manager);
	~NetworkServer();

	void Start(std::vector<FAcceptInfo> _accept_info_vector, std::vector<FConnectInfo> _connect_info_vector);
	void Stop();
	void Loop();
	bool Connect(ESessionType _session_type);
	
	virtual void OnAccept(std::shared_ptr<FSession> _session);
	virtual void OnConnect(std::shared_ptr<FSession> _session);
	virtual void OnDisconnect(std::shared_ptr<FSession> _session);

	void RegisterAcceptor(FAcceptInfo const& _accept_info);
	void RegisterConnector(FConnectInfo const& _connect_info);

	void PushNetEvent(ENetEventType _type, std::shared_ptr<IOService> _IO_service, std::shared_ptr<FSession> _session);

	void SendPacket(std::shared_ptr<FSession> _session, FBaseProtocol* _protocol);
	void ExecuteMessage(std::shared_ptr<FSession> _session, std::unique_ptr<byte[]> _data);

private:

	static SessionKey AddSessionKey() {
		static SessionKey session_key = 0;
		return ++session_key;
	}

private:
	std::vector<std::shared_ptr<IOService>> IO_service_vector;
	std::shared_ptr<ProtocolHandlerManager> protocol_handler_manager;

	SPSCQueue<std::shared_ptr<FNetEvent>> net_event_queue;
	std::queue<std::shared_ptr<FNetEvent>> wait_net_event_queue;

	std::map<SessionKey, std::shared_ptr<FSession>> connected_session_map;
	SessionMMap connected_server_map;
};

