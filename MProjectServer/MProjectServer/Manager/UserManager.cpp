#include "UserManager.h"
#include "Core/LogManager.h"
#include "User/MUser.h"

#include "Network/HeadServer.h"

std::weak_ptr<MUser> UserManager::ConnectUser(SessionKey _session_key) {
	if (true == user_map.contains(_session_key)) {
		GetLogger().lock()->WriteLog(ELogLevel::Warning, std::format("[UserManager::ConnectUser]User already connected[{}]", _session_key));
		return user_map[_session_key];
	}
	std::shared_ptr<MUser> user = std::make_shared<MUser>(
		HeadServer::GetMutableInstance().GetSession(_session_key),
		UserManager::GetUserKey()
	);
	user_map.emplace(_session_key, user);
	user_key_map.emplace(user->GetUserKey(), user);
	return std::weak_ptr<MUser>(user);
}

std::shared_ptr<MUser> UserManager::DisconnectUser(SessionKey _session_key) {
	if (false == user_map.contains(_session_key)) {
		return std::shared_ptr<MUser>();
	}
	std::shared_ptr<MUser> user = user_map[_session_key];
	user_map.erase(_session_key);
	user_key_map.erase(user->GetUserKey());
	return user;
}


//! Getter

std::weak_ptr<MUser> UserManager::GetUser(SessionKey _session_key) {
	if (false == user_map.contains(_session_key)) {
		return std::weak_ptr<MUser>();
	}
    return user_map[_session_key];
}

std::weak_ptr<MUser> UserManager::GetUserByKey(uint _user_key) {
	if (false == user_map.contains(_user_key)) {
		return std::weak_ptr<MUser>();
	}
	return user_map[_user_key];
}


//! Utility

void UserManager::ForEach(std::function<void(std::weak_ptr<MUser>)> _func) {
	for (auto& user : user_map) {
		_func(std::weak_ptr<MUser>(user.second));
	}
}


//! Getter

std::weak_ptr<ILogger> UserManager::GetLogger()
{
	if (true == logger.expired()) {
		logger = LogManager::GetMutableInstance().GetGenericLogger();
	}
	return logger;
}