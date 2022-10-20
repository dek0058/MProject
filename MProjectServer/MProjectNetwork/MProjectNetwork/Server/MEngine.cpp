#include "MEngine.h"
#include "Acceptor.h"
#include "MProjectNetwork/Core/Session.h"
#include "MProjectNetwork/Core/IOService.h"
#include "MProjectLogger/Logger/SpdLogger.h"
#include "Exception/BaseException.h"

namespace mproject {
namespace network {


MEngine::MEngine(FString _name, int _fps, ushort _acceptor_port)
	: ChiefThread(_name, _fps), acceptor_port(_acceptor_port) {

	IO_service = std::make_shared<IOService>();
}

MEngine::~MEngine() {
	OnStop();
}

void MEngine::OnStart() {
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
	catch (BaseException const& _exception) {
		logger->WriteLog(mproject::logger::ELogLevel::Critical, _exception.Message());
	}
	catch (std::exception _exception) {
		logger->WriteLog(mproject::logger::ELogLevel::Critical, FString(_exception.what()));
	}
}

void MEngine::OnUpdate() {
	// TODO: 일 분배
	
	// TODO: Sub Thread 완료 대기

	// TODO: 일 처리 완료
}

void MEngine::OnStop() {

	acceptor->Stop();

}

}	// network
}	// mproject
