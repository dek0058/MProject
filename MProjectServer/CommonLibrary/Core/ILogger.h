#pragma once
#include "CoreDefine.h"
#include "GlobalDefine.h"

class ILogger {
	static uint GetDelegateKey() {
		static uint key = 0;
		return key++;
	}

public:

	virtual void WriteLog(ELogLevel _log_level, std::string _msg) {
		if (false == is_initialize) {
			Create();
		}
		for (auto& Iter : log_delegate_map) {
			Iter.second(_log_level, _msg);
		}
	}

	/// <summary>
	/// When doing write log, called delegate.
	/// </summary>
	/// <returns>Unique key</returns>
	uint AddDelegate(std::function<void(ELogLevel, std::string const&)> _delegate) {
		uint key = GetDelegateKey();
		log_delegate_map.emplace(key, _delegate);
		return key;
	}

	void RemoveDelegate(uint _key) {
		if (false == log_delegate_map.contains(_key)) {
			WriteLog(ELogLevel::Error, std::format("[ILogger::RemoveDelegate]key not found. {}", _key));
			return;
		}
		log_delegate_map.erase(_key);
	}

protected:
	// Default Create
	virtual void Create() {
		is_initialize = true;
	}
private:
	bool is_initialize = false;
	std::map<uint, std::function<void(ELogLevel, std::string const&)>> log_delegate_map;
};
