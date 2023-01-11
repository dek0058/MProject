#include "MEngine.h"
#include "String/StringUtility.h"
#include "Acceptor.h"
#include "MProjectNetwork/Core/Session.h"
#include "MProjectNetwork/Core/IOService.h"
#include "MProjectLogger/Core/ILogger.h"
#include "Exception/ExceptionUtility.h"

namespace mproject {
namespace network {

using ELogLevel = logger::ELogLevel;

MEngine::MEngine(
	FString _name,
	int _fps,
	std::shared_ptr<Logger> _logger,
	size_t _session_count,
	size_t _receive_packet_capacity,
	size_t _max_packet_size,
	decimal _heartbeat_second
)
	: ChiefThread(_name, _fps, _logger)
	, receive_packet_capacity(_receive_packet_capacity)
	, max_packet_size(_max_packet_size)
	, heartbeat_second(_heartbeat_second)
	
	//! Session
	, origine_session_key(0)
	, session_pool(_session_count)

	//! Accpetor
	, acceptor_fps(_fps)
	, acceptor_port(Default_Acceptor_Port)
	, acceptor_receive_packet_capacity(_receive_packet_capacity)
	, acceptor_max_packet_size(_max_packet_size)
	, acceptor_heartbeat_second(_heartbeat_second)
	
{
	IO_service = std::make_shared<IOService>();
}

MEngine::~MEngine() {
}

void MEngine::OnStart() {
	size_t capacity = 0;

	// TODO: Create sub thread
	acceptor = std::make_shared<Acceptor>(
		acceptor_fps,
		std::static_pointer_cast<MEngine>(shared_from_this()),
		acceptor_port,
		IO_service->Get(),
		acceptor_receive_packet_capacity,
		acceptor_max_packet_size,
		acceptor_heartbeat_second
	);
	++capacity;

	sub_threads.reserve(capacity);
	
	// TODO: Add sub thread
	AddSubThread(acceptor);

	// start elite_thread...
	__super::OnStart();
}

void MEngine::OnUpdate() {
	__super::OnUpdate();
	// TODO: 일 분배

	// TODO: Sub Thread 완료 대기

	// TODO: 일 처리 완료
}

void MEngine::OnStop() {
	__super::OnStop();
	acceptor->Stop();
	acceptor.reset();
	IO_service->Stop();
	for (auto& thread : sub_threads) {
		thread->Join();
	}
	sub_threads.clear();
	WriteLog_Info(
		StringFormat::Format(FString(pTEXT("{} Stop complete.")), name.data)
	);
}

Session* MEngine::GetSession() {
	return (new (session_pool.Get()) (Session)(GetSessionKey(), IO_service->Get(), receive_packet_capacity, max_packet_size, heartbeat_second));
}

void MEngine::ReleaseSession(Session* _session) {
	if (nullptr != _session) {
		ReleaseSessionKey(_session->GetSessionKey());
		return session_pool.Release(_session);
	}
}

void MEngine::ConnectSession(Session* _session) {
	try {
		if (nullptr == _session) {
			throw MEXCEPTION(NullException, session);
		}

		if (connect_session_map.contains(_session->GetSessionKey())) {
			session_pool.Release(_session);
			throw MEXCEPTION_Param1(DuplicateException, connect_session_map, _session->GetSessionKey());
		}
	} catch (BaseException const& _me) {
		return GetLogger()->WriteLog(ELogLevel::Error, _me.What());
	} catch (std::exception const& _e) {
		return GetLogger()->WriteLog(ELogLevel::Error, FString(_e.what()));
	}
	
	connect_session_map.emplace(_session->GetSessionKey(), _session);
}

void MEngine::DisconnectSession(Session* _session) {
	try {
		if (nullptr == _session) {
			throw MEXCEPTION(NullException, session);
		}

		if (!connect_session_map.contains(_session->GetSessionKey())) {
			session_pool.Release(_session);
			throw MEXCEPTION_Param1(NotFoundException, connect_session_map, _session->GetSessionKey());
		}
	}
	catch (BaseException const& _me) {
		return GetLogger()->WriteLog(ELogLevel::Error, _me.What());
	}
	catch (std::exception const& _e) {
		return GetLogger()->WriteLog(ELogLevel::Error, FString(_e.what()));
	}

	auto iter = connect_session_map.find(_session->GetSessionKey());
	if (iter != connect_session_map.end()) {
		connect_session_map.erase(iter);
	}
	
	ReleaseSession(_session);
}

}	// network
}	// mproject
