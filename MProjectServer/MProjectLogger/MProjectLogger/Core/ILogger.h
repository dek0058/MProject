#pragma once

#include "Core/MObject.h"
#include "MProjectLogger/LogDefine.h"

namespace mproject {
namespace logger {
	
class ILogger {
public:
	void WriteLog(ELogLevel _level, FString _msg) {
		OnWrite(_level, _msg);
		msg.emplace_back(_level, _msg);
	}

	std::vector<std::tuple<ELogLevel, FString>> GetMessages() {
		std::vector<std::tuple<ELogLevel, FString>> result(msg.begin(), msg.end());
		msg.clear();
		return result;
	}

protected:
	virtual void OnWrite(ELogLevel _level, FString _msg) {}

private:
	std::list<std::tuple<ELogLevel, FString>> msg;
};

}	// logger
}	// mproject
