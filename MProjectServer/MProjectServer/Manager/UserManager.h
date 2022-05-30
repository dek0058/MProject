#pragma once

#include "Utility/TSingleton.h"
#include "Network/NetworkDefine.h"

class MUser;
class ILogger;

class UserManager : public TSingleton<UserManager> {
	
	template<typename T>
	using UserMap = std::map<T, std::shared_ptr<MUser>>;

	static uint GetUserKey() {
		static uint key = 0;
		return ++key;
	}
	
public:

	std::weak_ptr<MUser> ConnectUser(SessionKey _session_key);
	std::shared_ptr<MUser> DisconnectUser(SessionKey _session_key);

	//! Getter

	std::weak_ptr<MUser> GetUser(SessionKey _session_key);
	std::weak_ptr<MUser> GetUserByKey(uint _user_key);

	//! Utility

	void ForEach(std::function<void(std::weak_ptr<MUser>)> _func);

private:

	//! Getter
	
	std::weak_ptr<ILogger> logger;
	std::weak_ptr<ILogger> GetLogger();

private:

	UserMap<SessionKey> user_map;
	UserMap<uint> user_key_map;

};
