#include "ChiefThread.h"
#include "EliteThread.h"
#include "String/StringUtility.h"
#include "MProjectLogger/Logger/SpdLogger.h"
#include "MProjectNetwork/NetworkDefine.h"

namespace mproject {
namespace network {

using ELogLevel = logger::ELogLevel;

ChiefThread::ChiefThread(FString _name, int _fps) 
	: MThread(_fps), name(_name), fps(_fps) {
	logger = std::make_unique<logger::SpdLogger>(name, StringFormat::Format(pTEXT("./Logs/{}.log"), name.data));
}

ChiefThread::ChiefThread(FString _name, int _fps, std::shared_ptr<Logger> _logger)
	: MThread(_fps), name(_name), fps(_fps), logger(_logger) {
}

ChiefThread::~ChiefThread() {
	OnStop();
	// join.......
}

void ChiefThread::OnStart() {
	GetLogger()->WriteLog(
		ELogLevel::Info, 
		StringFormat::Format(FString(pTEXT("{} Start")), name.data)
	);
	
	stop_source = std::stop_source();
	for (auto& elite_thread : sub_threads) {
		if (elite_thread.get() != nullptr) {
			try {
				elite_thread->Start(stop_source.get_token());
			}
			catch (std::exception _exception) {
				return GetLogger()->WriteLog(ELogLevel::Critical, FString(_exception.what()));
			}
		}
	}
}

void ChiefThread::OnUpdate() {
	// TODO

}

void ChiefThread::OnStop() {
	stop_source.request_stop();

	WriteLog_Info(
		StringFormat::Format(FString(pTEXT("{} Stopping...")), name.data)
	);
}

void ChiefThread::AddSubThread(std::shared_ptr<EliteThread> _sub_thread) {
	sub_threads.emplace_back(_sub_thread);
}

void ChiefThread::WriteLog(logger::ELogLevel _level, FString _msg) {
	if (nullptr != GetLogger()) {
		GetLogger()->WriteLog(_level, _msg);
	}
}

void ChiefThread::WriteLog_Trace(FString _msg) {
	WriteLog(ELogLevel::Trace, _msg);
}

void ChiefThread::WriteLog_Debug(FString _msg) {
	WriteLog(ELogLevel::Debug, _msg);
}

void ChiefThread::WriteLog_Info(FString _msg) {
	WriteLog(ELogLevel::Info, _msg);
}

void ChiefThread::WriteLog_Warnining(FString _msg) {
	WriteLog(ELogLevel::Warning, _msg);
}

void ChiefThread::WriteLog_Error(FString _msg) {
	WriteLog(ELogLevel::Error, _msg);
}

void ChiefThread::WriteLog_Criticial(FString _msg) {
	WriteLog(ELogLevel::Critical, _msg);
}

}	// network
}	// mproject

