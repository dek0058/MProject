#include "UserManager.h"
#include "User/MUser.h"

#include "Network/HeadServer.h"

std::shared_ptr<MUser> UserManager::ConnectUser(SessionKey _session_key) {
	std::shared_ptr<MUser> user = std::make_shared<MUser>(
		HeadServer::GetMutableInstance().GetSession(_session_key),
		UserManager::GetUserKey()
	);
	user_map.emplace(_session_key, user);
	return user;
}

void UserManager::DisconnectUser(SessionKey _session_key) {
	if (false == user_map.contains(_session_key)) {
		return;
	}
	user_map.erase(_session_key);
}

std::shared_ptr<MUser> UserManager::GetUser(SessionKey _session_key) {
	if (false == user_map.contains(_session_key)) {
		return nullptr;
	}
    return user_map[_session_key];
}

void UserManager::ForEach(std::function<void(std::shared_ptr<MUser>)> _func) {
	for (auto& user : user_map) {
		_func(user.second);
	}
}
