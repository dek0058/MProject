#include "HeadServer.h"
#include "HeadProtocolHandlerManager.h"
#include "Core/LogManager.h"

#include "Network/Session.h"
#include "Manager/UserManager.h"
#include "Manager/WorldManager.h"

#include "World/LoginWorld.h"
#include "User/MUser.h"

HeadServer::HeadServer() : NetworkServer(std::make_shared<HeadProtocolHandlerManager>()) {
}

HeadServer::~HeadServer() {

}

void HeadServer::OnAccept(std::shared_ptr<FSession> _session) {
	NetworkServer::OnAccept(_session);
	LogManager::GetMutableInstance().GenericLog(ELogLevel::Trace, "HeadServer", "OnAccept", "User Accept");

	auto user = UserManager::GetMutableInstance().ConnectUser(_session->GetSessionKey());
	auto world = WorldManager::GetMutableInstance().FindWorld<LoginWorld>();
	WorldManager::GetMutableInstance().JoinUserToWorld(user, world.lock()->GetWorldKey());
}

void HeadServer::OnConnect(std::shared_ptr<FSession> _session) {
	NetworkServer::OnConnect(_session);
	
}

void HeadServer::OnDisconnect(std::shared_ptr<FSession> _session) {
	NetworkServer::OnDisconnect(_session);
	
	auto user = UserManager::GetMutableInstance().DisconnectUser(_session->GetSessionKey());
	WorldManager::GetMutableInstance().LeaveUserFromWorld(user);
	if (nullptr == user.get()) {
		return;
	}
	LogManager::GetMutableInstance().GenericLog(ELogLevel::Trace, "HeadServer", "OnDisconnect", "User Disconnected");
}
