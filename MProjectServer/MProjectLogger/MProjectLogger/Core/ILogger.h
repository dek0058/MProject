#pragma once

#include "Core/MObject.h"
#include "MProjectLogger/LogDefine.h"

namespace mproject {
namespace logger {
	
class ILogger {
public:
	template<typename T>
		requires DefaultStringType<T> || std::is_same_v<T, FString>
	void WriteLog(ELogLevel _level, T _msg) {
		OnWrite(_level, _msg);
		msg.emplace_back(_level, _msg);
	}

	bool IsEmpty() const {
		return msg.empty();
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
