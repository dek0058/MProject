#pragma once

#include "NetworkDefine.h"

#include "Utility/SPSCQueue.h"

class Session;

class SessionObserver : std::enable_shared_from_this<SessionObserver> {
	
	

public:

	std::shared_ptr<Session> GetSession() {
		return nullptr;
	}


private:

	

};

