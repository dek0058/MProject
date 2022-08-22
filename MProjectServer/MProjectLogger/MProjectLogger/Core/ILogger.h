#pragma once

#include "Core/MObject.h"
#include "MProjectLogger/LogDefine.h"

namespace mproject {
namespace logger {
	
template<
	typename MsgType,
	typename MsgTypeEnabled = typename std::enable_if_t<is_str<MsgType>::value, MsgType>
>
class ILogger : public MObject {
public:
	ILogger(uint _max_size = 10000) : max_size(_max_size) { }

public:
	void WriteLog(ELogLevel _level, MsgType _msg) {
		OnWrite(_level, _msg);
		if (msg.size() < max_size) {
			msg.emplace_back(_level, _msg);
		}
	}

	std::vector<std::tuple<ELogLevel, MsgType>> GetMessages() {
		std::vector<std::tuple<ELogLevel, MsgType>> result(msg.begin(), msg.end());
		msg.clear();
		return result;
	}

protected:
	virtual void OnWrite(ELogLevel _level, MsgType _msg) {}

private:
	std::list<std::tuple<ELogLevel, MsgType>> msg;
	uint max_size;
};

}	// logger
}	// mproject
