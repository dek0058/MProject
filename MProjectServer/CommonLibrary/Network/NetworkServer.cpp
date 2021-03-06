#include "NetworkServer.h"

#include "IOAcceptor.h"
#include "IOConnector.h"
#include "NetEvent.h"
#include "Session.h"
#include "BaseProtocol.h"
#include "Core/LogManager.h"


NetworkServer::NetworkServer(std::shared_ptr<ProtocolHandlerManager> _handler_manager) : protocol_handler_manager(_handler_manager), net_event_queue(NET_EVENT_CAPCITY) {
}

NetworkServer::~NetworkServer() {

}

void NetworkServer::Start(std::vector<FAcceptInfo> _accept_info_vector, std::vector<FConnectInfo> _connect_info_vector) {
	protocol_handler_manager->OnRegisterHandler();
	
	// Setting connect accpetor object session
	for (FAcceptInfo const& accept_info : _accept_info_vector) {
		if (true == accept_info.ip.empty()) {
			continue;
		}
		RegisterAcceptor(accept_info);
	}

	// Setting connector object session
	for (FConnectInfo const& connect_info : _connect_info_vector) {
		if (true == connect_info.ip.empty()) {
			continue;
		}
		RegisterConnector(connect_info);
	}
}

void NetworkServer::Stop() {
	for (auto const& IO_service : IO_service_vector) {
		IO_service->Stop();
	}
}

void NetworkServer::Loop() {
	for (auto& IO_service : IO_service_vector) {
		IO_service->Loop();
	}

	while (false == net_event_queue.empty()) {
		if (nullptr == net_event_queue.front()) {
			net_event_queue.pop();
			continue;
		}
		std::shared_ptr<FNetEvent> net_event = *net_event_queue.front();
		net_event_queue.pop();

		switch (net_event->net_event_type) {
			case ENetEventType::Accepted: {
				OnAccept(net_event->session);
			} break;
			case ENetEventType::Connected: {
				OnConnect(net_event->session);
			} break;
			case ENetEventType::Disconnected: {
				auto iter = connected_session_map.find(net_event->session->GetSessionKey());
				if (iter != connected_session_map.end()) {
					OnDisconnect(net_event->session);
				} else {
					net_event->session->Disconnect();
					// error 연결은 되었지만 데이터가 저장되어 있지 않음
				}
				net_event->IO_service->PushSession(net_event->session);
			
			} break;
			case ENetEventType::Error: {
				LogManager::GetMutableInstance().GenericLog(ELogLevel::Error, "NetworkServer", "Loop", "Server error occuured!!!");
			} break;
			default: {
				LogManager::GetMutableInstance().GenericLog(ELogLevel::Error, "NetworkServer", "Loop", "Unknown!!!");
			} break;
		}
	}

	while (false == wait_net_event_queue.empty()) {
		if (true == net_event_queue.try_emplace(wait_net_event_queue.front())) {
			wait_net_event_queue.pop();
		}
	}

	for (auto& pair : connected_session_map) {
		if (pair.second->ReceiveBufferSize() > 0)
		{
			pair.second->Flush();
		}
	}

}

bool NetworkServer::Connect(ESessionType _session_type) {
	for (auto& IO_service : IO_service_vector) {
		if (IO_service->GetSessionType() == _session_type) {
			return IO_service->Connect();
		}
	}
	return false;
}

void NetworkServer::OnAccept(std::shared_ptr<FSession> _session) {
	_session->Accept(AddSessionKey());
	connected_session_map.emplace(_session->GetSessionKey(), _session);
}

void NetworkServer::OnConnect(std::shared_ptr<FSession> _session) {
	_session->Connect(AddSessionKey());
	connected_session_map.emplace(_session->GetSessionKey(), _session);
}

void NetworkServer::OnDisconnect(std::shared_ptr<FSession> _session) {
	connected_session_map.erase(_session->GetSessionKey());
	_session->Disconnect();
}

void NetworkServer::RegisterAcceptor(FAcceptInfo const& _accept_info) {
	std::shared_ptr<IOAcceptor> IO_acceptor(new IOAcceptor(this));
	IO_acceptor->Start(_accept_info);
	IO_service_vector.emplace_back(IO_acceptor);
}

void NetworkServer::RegisterConnector(FConnectInfo const& _connect_info) {
	std::shared_ptr<IOConnector> IO_connect(new IOConnector(this));
	IO_connect->Start(_connect_info);
	IO_service_vector.emplace_back(IO_connect);
}

void NetworkServer::PushNetEvent(ENetEventType _type, std::shared_ptr<IOService> _IO_service, std::shared_ptr<FSession> _session) {
	std::shared_ptr<FNetEvent> net_event(new FNetEvent(_type, _IO_service, _session));
	if (false == net_event_queue.try_emplace(net_event)) {
		// error
	}
}

void NetworkServer::SendPacket(SessionKey _session, std::unique_ptr<FPacket> _packet) {
	if (false == connected_session_map.contains(_session)) {
		return;
	}
	connected_session_map[_session]->Write(std::move(_packet));
}

void NetworkServer::SendPacket(SessionKey _session, std::vector<uint> _tags) {
	if (false == connected_session_map.contains(_session)) {
		return;
	}
	connected_session_map[_session]->Write(std::move(GetHandlerManager()->CreateProtocolMessage(_tags)));
}

void NetworkServer::ExecuteMessage(std::shared_ptr<FSession> _session, std::unique_ptr<FPacket> _packet) {
	protocol_handler_manager->ReceivePacket(_session, std::move(_packet));
}

std::shared_ptr<FSession> NetworkServer::GetSession(SessionKey _session_key) {
	if (false == connected_session_map.contains(_session_key)) {
		return nullptr;
	} else {
		return connected_session_map[_session_key];
	}
}
