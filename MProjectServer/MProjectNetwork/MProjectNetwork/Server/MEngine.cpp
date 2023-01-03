#include "MEngine.h"
#include "Acceptor.h"
#include "MProjectNetwork/Core/Session.h"
#include "MProjectNetwork/Core/IOService.h"
#include "MProjectLogger/Core/ILogger.h"
#include "Exception/BaseException.h"

namespace mproject {
namespace network {

using ELogLevel = logger::ELogLevel;

MEngine::MEngine(
	FString _name,
	int _fps,
	std::shared_ptr<Logger> _logger,
	ushort _acceptor_port,
	size_t _session_count,
	size_t _receive_packet_capacity,
	size_t _max_packet_size,
	decimal _heartbeat_second
)
	: ChiefThread(_name, _fps, _logger)
	, acceptor_port(_acceptor_port) 
	, session_pool(_session_count)
	, receive_packet_capacity(_receive_packet_capacity)
	, max_packet_size(_max_packet_size)
	, heartbeat_second(_heartbeat_second)
{
	IO_service = std::make_shared<IOService>();
}

MEngine::~MEngine() {
}

void MEngine::OnStart() {
	__super::OnStart();
	size_t capacity = 0;

	// TODO: Create sub thread
	acceptor = std::make_shared<Acceptor>(fps, std::static_pointer_cast<MEngine>(shared_from_this()), acceptor_port);
	++capacity;

	sub_threads.reserve(capacity);
	
	// TODO: Add sub thread
	AddSubThread(acceptor);

	try {
		acceptor->Start(stop_source.get_token());
	}
	catch (BaseException _exception) {
		GetLogger()->WriteLog(ELogLevel::Critical, _exception.Message());
	}
	catch (std::exception _exception) {
		GetLogger()->WriteLog(ELogLevel::Critical, FString(_exception.what()));
	}
}

void MEngine::OnUpdate() {
	__super::OnUpdate();
	// TODO: 일 분배

	// TODO: Sub Thread 완료 대기

	// TODO: 일 처리 완료
}

void MEngine::OnStop() {
	__super::OnStop();
}

Session* MEngine::GetSession() {
	return (new (session_pool.Get()) (Session)(IO_service->Get(), receive_packet_capacity, max_packet_size, heartbeat_second));
}

void MEngine::ReleaseSession(Session* _session) {
	if (nullptr != _session) {
		return session_pool.Release(_session);
	}
}

}	// network
}	// mproject
