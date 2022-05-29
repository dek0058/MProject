#pragma once
#include "Utility/MThread.h"
#include "Utility/TSingleton.h"
#include "ILogger.h"


class LogThread : public MThread {
	enum class ELogCoreType : char {
		Generic,
	};

public:
	LogThread() : MThread(L"Log", 10) {}


	//! Generic
	void GenericLog(ELogLevel _log_level, std::string const& _file_name, std::string const& _func_name, std::string const& _msg) {
		std::string msg = std::format("[{}::{}]{}", _file_name, _func_name, _msg);
		messages[ELogCoreType::Generic].emplace_back(std::make_tuple(_log_level, msg));
	}
	
	std::shared_ptr<ILogger> GetGenericLogger() {
		return loggers[ELogCoreType::Generic];
	}

protected:

	virtual void OnStart() override;
	virtual void OnUpdate() override;

private:
	
	std::map<ELogCoreType, std::list<std::tuple<ELogLevel, std::string>>> messages;
	std::map<ELogCoreType, std::shared_ptr<ILogger>> loggers;
};
