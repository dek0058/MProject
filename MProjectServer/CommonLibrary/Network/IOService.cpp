#include "MProjectServerDefine.h"
#include "IOService.h"

#include "NetworkServer.h"
#include "Session.h"



IOService::IOService(std::shared_ptr<NetworkServer> _network_server) 
	: strand(IO_service), network_server(_network_server), is_stopped(false), session_queue(SESSION_CAPACITY) {

}

IOService::~IOService() {
	if (true == is_stopped.load()) {
		return;
	}
	Stop();
}

void IOService::Start(uint _thread_count) {
	for (uint i = 0; i < _thread_count; ++i) {
		IO_thread_group.create_thread([this]() {IO_service.run(); });
	}
}

void IOService::Stop() {
	if (true == is_stopped.load()) {
		return;
	}
	is_stopped.store(true);

	IO_service.stop();
	IO_thread_group.join_all();
}

void IOService::PushSession(std::shared_ptr<FSession> _session) {
	if (!session_queue.try_emplace(_session)) {
		// error
	}
}

bool IOService::PopSession(std::shared_ptr<FSession>& _session) {
	if (true == session_queue.empty()) {
		// error
		return false;
	}
	_session = *session_queue.front();
	session_queue.pop();
	return true;
}

void IOService::PushNetEvent(ENetEventType _type, std::shared_ptr<FSession> _session) {
	network_server->PushNetEvent(_type, shared_from_this(), _session);
}
