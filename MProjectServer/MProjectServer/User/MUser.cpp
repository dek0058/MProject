#include "MUser.h"
#include "Network/Session.h"


MUser::MUser(std::shared_ptr<FSession> _session, uint _key)
	: session(_session), key(_key),
	game_player_controller(new GPC()) {
	

}

MUser::~MUser() {
	
}


uint MUser::SessionKey() const {
	return session->GetSessionKey();
}

uint MUser::GetUserKey() const {
	return key;
}


