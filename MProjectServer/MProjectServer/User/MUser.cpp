#include "MUser.h"
#include "Network/Session.h"
#include "Network/BaseProtocol.h"
#include "Network/HeadServer.h"

MUser::MUser(std::shared_ptr<FSession> _session, uint _key)
	: session(_session), key(_key),
	game_player_controller(new GPC(key))
{
	tags.clear();
}

uint MUser::SessionKey() const {
	return session->GetSessionKey();
}

uint MUser::GetUserKey() const {
	return key;
}

void MUser::SendPacket(std::unique_ptr<FPacket> _packet) {
	HeadServer::GetMutableInstance().SendPacket(SessionKey(), std::move(_packet));
}


