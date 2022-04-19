#pragma once

#include "spdlog/spdlog.h"

#include "Utility/TSingleton.h"

#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#include <functional>

class MLogger : public TSingleton<MLogger> {
	using LogDeleagte = std::vector<std::function<void()>>;

protected:
	MLogger();
	
public:
	
	void Create(std::string_view _name, std::string_view _path, size_t _max_size, size_t _max_files);
	
	void FlushEvery(size_t _seconds);

	void LogInfo(std::string_view _msg);
	void LogWarning(std::string_view _msg);
	void LogError(std::string_view _msg);

	void PushMessage(std::string_view _msg);
	std::string PopMessage();

	void AddDelegate(std::function<void()> _delegate);

private:
	LogDeleagte& GetLogDelegate() {
		return log_delegate_map[logger];
	}

private:
	
	std::shared_ptr<spdlog::logger> logger;

	std::list<std::string> log_buffer;
	
	std::unordered_map<std::shared_ptr<spdlog::logger>, LogDeleagte> log_delegate_map;

	bool is_initailize;
};

