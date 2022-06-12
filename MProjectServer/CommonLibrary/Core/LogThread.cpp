#include "LogThread.h"
#include "GenericLogger.h"

void LogThread::OnStart() {
	MThread::OnStart();

	// TODO
	loggers.emplace(ELogCoreType::Generic, std::make_shared<GenericLogger>());
}

void LogThread::OnUpdate() {
	for (auto& Iter : loggers) {
		if (true == messages[ELogCoreType::Generic].empty()) {
			continue;
		}
		auto [level, msg] = messages[ELogCoreType::Generic].front();
		messages[ELogCoreType::Generic].pop_front();
		Iter.second->WriteLog(level, msg);
	}
}
