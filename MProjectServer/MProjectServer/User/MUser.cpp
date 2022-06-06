#include "MUser.h"
#include "Core/LogManager.h"
#include "Network/Session.h"
#include "Network/BaseProtocol.h"
#include "Network/HeadServer.h"
#include "World/MWorld.h"
#include "Structure/Player/GPC.h" // include ActorStructure.h


MUser::MUser(std::shared_ptr<FSession> _session, uint _key)
	: session(_session), key(_key),
	game_player_controller(new GPC(key))
{
	tags.clear();
}

void MUser::SendPacket(std::unique_ptr<FPacket> _packet) {
	HeadServer::GetMutableInstance().SendPacket(SessionKey(), std::move(_packet));
}

void MUser::SendTag() {
	HeadServer::GetMutableInstance().SendPacket(SessionKey(), GetPacketTagList());

}

void MUser::SetWorld(std::shared_ptr<MWorld> _world) {
	world = std::weak_ptr<MWorld>(_world);
	tags = world.lock()->GetTags();
}

void MUser::ResetWorld() {
	tags.clear();
	world.reset();
}

uint MUser::SessionKey() const {
	return session->GetSessionKey();
}


std::weak_ptr<ILogger> MUser::GetLogger() {
	if (true == logger.expired()) {
		logger = LogManager::GetMutableInstance().GetGenericLogger();
	}
	return logger;
}

