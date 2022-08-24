#include "SessionPool.h"
#include "IOService.h"
#include "Session.h"


#include <boost/uuid/uuid_generators.hpp>

namespace mproject {
namespace network {

//! SessionPool
SessionPool::SessionPool(std::shared_ptr<IOService> _IO_Service, size_t _max_size) 
	: IO_service(_IO_Service),
	  max_size(_max_size),
	  cur_size(0) {
	stores.reserve(_max_size);
	active_session.reserve(_max_size);
}


//! SessionPool_TCP
SessionPool_TCP::SessionPool_TCP(std::shared_ptr<IOService> _IO_service, size_t _max_size) 
	: SessionPool(_IO_service, _max_size) {
	
	for (size_t i = 0; i < _max_size; ++i) {
		
	}
	

}

SessionPool_TCP::~SessionPool_TCP() {
	/*for (auto& [key, session] : active_session) {
		session->Close();
	}
	active_session.clear();
	stores.clear();*/
	max_size = cur_size = 0;
}

std::shared_ptr<Session> SessionPool_TCP::Get()
{
	if (IsFull()) {
		return nullptr;
	}
	return nullptr;
	//std::shared_ptr<Session> result = stores[0];
	//
	//active_session.emplace(result->GetSessionKey(), result);
	//
	//++cur_size;
	//return result;
}

void SessionPool_TCP::Release(SessionKey _session_key)
{
}

}   // network
}   // mproject

