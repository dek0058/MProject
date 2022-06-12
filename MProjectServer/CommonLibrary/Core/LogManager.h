#pragma once
#include "LogThread.h"
#include "Utility/MThread.h"
#include "Utility/TSingleton.h"

class LogManager : public TSingleton<LogManager> {
protected:
	
	LogManager() : thread(new LogThread()) {
		thread->Start();
	}

public:
	~LogManager() {
		thread->Stop();
	}

	void GenericLog(ELogLevel _log_level, std::string const& _file_name, std::string const& _func_name, std::string _msg) {
		thread->GenericLog(_log_level, _file_name, _func_name, _msg);
	}

	std::weak_ptr<ILogger> GetGenericLogger() {
		return std::weak_ptr<ILogger>(thread->GetGenericLogger());
	}

private:
	std::shared_ptr<LogThread> thread;
};

