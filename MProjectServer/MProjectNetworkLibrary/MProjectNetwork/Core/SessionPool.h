#pragma once

//! Library
#include "MProjectNetwork/NetworkDefine.h"


namespace mproject {
namespace network {

class IOService;
class Session_TCP;

class SessionPool_TCP {
	
public:
	SessionPool_TCP(std::shared_ptr<IOService> _IO_service, size_t _max_size);
	~SessionPool_TCP();

	std::shared_ptr<Session_TCP> Get();
	void Release(std::shared_ptr<Session_TCP> _session);

private:

	std::shared_ptr<IOService> IO_service;

	std::vector<std::shared_ptr<Session_TCP>> stores;
	std::unordered_map<SessionKey, std::shared_ptr<Session_TCP>> active_session;

};

}	// network
}	// mproject