#include "ChiefThread.h"
#include "EliteThread.h"
#include "String/StringFormat.h"
#include "MProjectLogger/Logger/SpdLogger.h"
#include "MProjectNetwork/NetworkDefine.h"

namespace mproject {
namespace network {

ChiefThread::ChiefThread(FString _name, int _fps) 
	: MThread(_fps), name(_name), fps(_fps) {
	logger = std::make_unique<logger::SpdLogger>(name, StringFormat::Format(pTEXT("./Logs/{}.log"), name.data));
}

ChiefThread::ChiefThread(FString _name, int _fps, std::shared_ptr<logger::ILogger> _logger)
	: MThread(_fps), name(_name), fps(_fps), logger(_logger) {
}

ChiefThread::~ChiefThread() {
	OnStop();
	// join.......
}

void ChiefThread::OnStart() {
	logger->WriteLog(
		mproject::logger::ELogLevel::Info, 
		StringFormat::Format(FString(pTEXT("{} Start")), name.data)
	);
	
	for (auto& elite_thread : sub_threads) {
		if (elite_thread.get() != nullptr) {
			elite_thread->Start(stop_source.get_token());
		}
	}
}

void ChiefThread::OnUpdate() {
	// TODO

}

void ChiefThread::OnStop() {
	stop_source.request_stop();

	logger->WriteLog(
		mproject::logger::ELogLevel::Info,
		StringFormat::Format(FString(pTEXT("{} Stop")), name.data)
	);
}

void ChiefThread::AddSubThread(std::shared_ptr<EliteThread> _sub_thread) {
	sub_threads.emplace_back(_sub_thread);
}

}	// network
}	// mproject

