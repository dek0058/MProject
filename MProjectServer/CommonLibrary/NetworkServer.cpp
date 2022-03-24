#include "NetworkServer.h"
#include "MProjectServerDefine.h"

#include "IOAcceptor.h"
#include "IOConnector.h"
#include "NetEvent.h"


NetworkServer::NetworkServer() : net_event_queue(NET_EVENT_CAPCITY) {
	protocol_handler_manager.reset();
}

NetworkServer::~NetworkServer() {

}

void NetworkServer::Start(std::vector<FAcceptInfo> _accept_info_vector, std::vector<FConnectInfo> _connect_info_vector) {
	protocol_handler_manager->OnRegisterHandler();
	
	for (FAcceptInfo const& accept_info : _accept_info_vector) {
		if (true == accept_info.ip.empty()) {
			continue;
		}
		RegisterAcceptor(accept_info);
	}

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

			} break;
			case ENetEventType::Connected: {

			} break;
			case ENetEventType::Disconnected: {

			} break;
			case ENetEventType::Error: {

			} break;
			default: {

			} break;
		}
	}

	while (false == wait_net_event_queue.empty()) {
		if (true == net_event_queue.try_emplace(wait_net_event_queue.front())) {
			wait_net_event_queue.pop();
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


void NetworkServer::RegisterAcceptor(FAcceptInfo const& _accept_info) {
	std::unique_ptr<IOAcceptor> IO_acceptor(new IOAcceptor(shared_from_this()));
	IO_acceptor->Start(_accept_info);
	IO_service_vector.emplace_back(std::move(IO_acceptor));
}

void NetworkServer::RegisterConnector(FConnectInfo const& _connect_info) {
	std::unique_ptr<IOConnector> IO_connect(new IOConnector(shared_from_this()));
	IO_connect->Start(_connect_info);
	IO_service_vector.emplace_back(std::move(IO_connect));
}

