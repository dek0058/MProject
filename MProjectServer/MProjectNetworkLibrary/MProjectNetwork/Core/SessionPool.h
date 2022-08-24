#pragma once

//! Library
#include "MProjectNetwork/NetworkDefine.h"


namespace mproject {
namespace network {

class IOService;
class Session;

class SessionPool {
	
public:
	SessionPool(std::shared_ptr<IOService> _IO_Service, size_t _max_size);

public:
	virtual std::shared_ptr<Session> Get() = 0;
	virtual void Release(SessionKey _session_key) = 0;

	//! Getter
	bool IsFull() const {
		return cur_size >= max_size;
	}

protected:
	std::vector<std::shared_ptr<Session>> stores;
	std::unordered_map<SessionKey, std::shared_ptr<Session>> active_session;
	
	std::shared_ptr<IOService> IO_service;

	size_t max_size;
	size_t cur_size;
};

class SessionPool_TCP : public SessionPool {
	
public:
	SessionPool_TCP(std::shared_ptr<IOService> _IO_service, size_t _max_size);
	~SessionPool_TCP();

	std::shared_ptr<Session> Get();
	void Release(SessionKey _session_key);
};

}	// network
}	// mproject