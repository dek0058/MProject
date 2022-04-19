#include "MLogger.h"

//#include "spdlog/sinks/stdout_color_sinks.h" //console
#include "spdlog/sinks/rotating_file_sink.h"

#include <format>

MLogger::MLogger() : is_initailize(false) {
	

}

void MLogger::Create(std::string_view _name, std::string_view _path, size_t _max_size, size_t _max_files) {
	is_initailize = true;
	logger = spdlog::rotating_logger_mt(_name.data(), std::format("{}/{}.log", _path, _name), _max_size, _max_files);
	logger->flush_on(spdlog::level::warn);
}

void MLogger::FlushEvery(size_t _seconds) {
	if (false == is_initailize) {
		return;
	}
	spdlog::flush_every(std::chrono::seconds(_seconds));
}

void MLogger::LogInfo(std::string_view _msg) {	
	if (false == is_initailize) {
		return;
	}
	if (true == _msg.empty()) {
		return;
	}
	logger->info(_msg.data());
	PushMessage(_msg);

	LogDeleagte& log_delegate = GetLogDelegate();
	for (LogDeleagte::iterator iter = log_delegate.begin(); iter != log_delegate.end(); ++iter) {
		(*iter)();
	}
}

void MLogger::LogWarning(std::string_view _msg) {
	if (false == is_initailize) {
		return;
	}
	if (true == _msg.empty()) {
		return;
	}
	logger->warn(_msg.data());
	PushMessage(_msg);

	LogDeleagte& log_delegate = GetLogDelegate();
	for (LogDeleagte::iterator iter = log_delegate.begin(); iter != log_delegate.end(); ++iter) {
		(*iter)();
	}
}

void MLogger::LogError(std::string_view _msg) {
	if (false == is_initailize) {
		return;
	}
	if (true == _msg.empty()) {
		return;
	}
	logger->error(_msg.data());
	PushMessage(_msg);
	
	LogDeleagte& log_delegate = GetLogDelegate();
	for (LogDeleagte::iterator iter = log_delegate.begin(); iter != log_delegate.end(); ++iter) {
		(*iter)();
	}
}

void MLogger::PushMessage(std::string_view _msg) {
	if (true == _msg.empty()) {
		return;
	}
	log_buffer.emplace_back(_msg);
}

std::string MLogger::PopMessage() {
	if (true == log_buffer.empty()) {
		return std::string();
	}
	std::string result = log_buffer.front();
	log_buffer.pop_front();
	return result;
}

void MLogger::AddDelegate(std::function<void()> _delegate) {
	if (false == is_initailize) {
		return;
	}
	if (nullptr == _delegate) {
		return;
	}
	LogDeleagte& log_delegate = GetLogDelegate();
	log_delegate.emplace_back(_delegate);
}
