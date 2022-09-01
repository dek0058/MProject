#include "SessionPool.h"
#include "IOService.h"
#include "Session.h"


#include <boost/uuid/uuid_generators.hpp>

namespace mproject {
namespace network {

//! SessionPool
SessionPool::SessionPool(std::shared_ptr<IOService> _IO_service, size_t _max_size, ESessionType _session_type)
	: wait_queue(_max_size),
	  IO_service(_IO_service),
	  max_size(_max_size),
	  cur_size(0),
	  session_type(_session_type) {
	
	sessions.reserve(max_size);
}

SessionPool::~SessionPool() {
	for (auto [guid, data] : sessions) {
		if (nullptr == data.session) {
			continue;
		}
		if (true == data.occupied) {
			data.session->Shutdown();
		} else {
			data.session->Close();
		}
	}
}

//! SessionPool_TCP

void SessionPool_TCP::Initialize() {
	for (size_t i = 0; i < max_size; ++i) {
		std::shared_ptr<Session_TCP> session = std::make_shared<Session_TCP>(IO_service, session_type);
		session->SetParent(shared_from_this());
		if (!sessions.contains(session->ToString())) {
			sessions.emplace(session->ToString(), FSessionPoolData(std::static_pointer_cast<Session>(session)));
			wait_queue.emplace(session->ToString());
		}
	}
	if (max_size != sessions.size()) {
		// 예외처리 날려보자. 초기화가 안된건 큰일이다.
	}
}

std::shared_ptr<Session> SessionPool_TCP::Get() {
	if (true == wait_queue.empty()) {
		return nullptr;
	}
	const std::string guid = *wait_queue.front();
	wait_queue.pop();
	FSessionPoolData& data = sessions[guid];
	data.occupied = true;
	return data.session;
}

void SessionPool_TCP::Release(std::shared_ptr<Session> _session) {
	if (nullptr == _session) {
		return;
	}
	const std::string guid = _session->ToString();
	FSessionPoolData& data = sessions[guid];
	if (false == data.occupied) {
		return;
	}
	wait_queue.emplace(guid);
	data.occupied = false;
}

}   // network
}   // mproject

