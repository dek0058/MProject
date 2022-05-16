#include "UserManager.h"
#include "User/MUser.h"

#include "Network/HeadServer.h"

MUser* UserManager::ConnectUser(SessionKey _session_key) {
	
	MUser* user = new MUser(HeadServer::GetMutableInstance().GetSession(_session_key));
	user_map.emplace(_session_key, user);
	return user;
}

void UserManager::DisconnectUser(SessionKey _session_key) {
	if (false == user_map.contains(_session_key)) {
		return;
	}
	user_map.erase(_session_key);
}

MUser* UserManager::GetUser(SessionKey _session_key) {
	if (false == user_map.contains(_session_key)) {
		return nullptr;
	}
    return user_map[_session_key];
}

void UserManager::ForEach(std::function<void(MUser*)> _func) {
	
}
