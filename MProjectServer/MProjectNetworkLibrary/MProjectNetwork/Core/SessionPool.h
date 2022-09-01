#pragma once

#include <boost/uuid/uuid.hpp>

//! Library
#include "MProjectNetwork/NetworkDefine.h"
#include "Utility/SPSCQueue.h"

#include "SessionPoolData.h"

namespace mproject {
namespace network {

class IOService;
class Session;

class SessionPool : public std::enable_shared_from_this<SessionPool> {
	
public:
	SessionPool(std::shared_ptr<IOService> _IO_service, size_t _max_size, ESessionType _session_type);
	~SessionPool();

public:
	virtual void Initialize() = 0;

	virtual std::shared_ptr<Session> Get() = 0;
	virtual void Release(std::shared_ptr<Session> _session) = 0;

protected:
	std::unordered_map<std::string, FSessionPoolData> sessions;
	SPSCQueue<std::string> wait_queue;

	std::shared_ptr<IOService> IO_service;
	size_t max_size;
	size_t cur_size;
	ESessionType session_type;
};

class SessionPool_TCP : public SessionPool {
	
public:
	void Initialize() override;
	std::shared_ptr<Session> Get();
	void Release(std::shared_ptr<Session> _session);
};

}	// network
}	// mproject