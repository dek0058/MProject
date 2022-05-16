#pragma once

#include "Utility/TSingleton.h"
#include "Utility/MemoryPool.h"
#include "Network/NetworkDefine.h"

class MUser;

class UserManager : public TSingleton<UserManager> {
	
	using UserMap = std::map<SessionKey, MUser*>;

	
	
public:

	MUser* ConnectUser(SessionKey _session_key);
	void DisconnectUser(SessionKey _session_key);

	//! Getter

	MUser* GetUser(SessionKey _session_key);


	//! Iterator

	void ForEach(std::function<void(MUser*)> _func);

private:

	
	UserMap user_map;

};
