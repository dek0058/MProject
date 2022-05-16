#include "MUser.h"
#include "Network/Session.h"


MUser::MUser(std::shared_ptr<FSession> _session) 
	: session(_session), user_key(GetTestUserKey()) {
	

}

MUser::~MUser() {
	delete this;
}


uint MUser::SessionKey() const {
	return session->GetSessionKey();
}

uint MUser::GetUserKey() const {
	return user_key;
}


