#pragma once

#include "Utility/TSingleton.h"
#include "Network/NetworkDefine.h"

class MUser;

class UserManager : public TSingleton<UserManager> {
	
	using UserMap = std::map<SessionKey, std::shared_ptr<MUser>>;

	static int GetUserKey() {
		static int key = 0;
		return ++key;
	}
	
public:

	std::shared_ptr<MUser> ConnectUser(SessionKey _session_key);
	void DisconnectUser(SessionKey _session_key);

	//! Getter

	std::shared_ptr<MUser> GetUser(SessionKey _session_key);


	//! Iterator

	void ForEach(std::function<void(std::shared_ptr<MUser>)> _func);

private:

	
	UserMap user_map;

};
