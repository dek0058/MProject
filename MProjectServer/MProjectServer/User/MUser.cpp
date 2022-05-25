#include "MUser.h"
#include "Network/Session.h"
#include "Network/BaseProtocol.h"

MUser::MUser(std::shared_ptr<FSession> _session, uint _key)
	: session(_session), key(_key),
	game_player_controller(new GPC(key)) {
	

}

uint MUser::SessionKey() const {
	return session->GetSessionKey();
}

uint MUser::GetUserKey() const {
	return key;
}

void MUser::SendPacket(std::unique_ptr<FPacket> _packet)
{
}


