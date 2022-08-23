#pragma once

#include "MProjectLogger/Core/ILogger.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"

namespace mproject {
namespace logger {

class SpdLogger final : public ILogger<std::string> {

public:
	SpdLogger(std::string _name, std::string _path, size_t _max_size, size_t max_files) : 
		name(_name),
		path(_path),
		max_size(_max_size),
		max_files(max_files) {
		logger = spdlog::rotating_logger_mt(name.data(), std::format("{}/{}.log", path, name), max_size, max_files);
		logger->flush_on(spdlog::level::warn);
	}

protected:

	virtual void OnWrite(ELogLevel _level, std::string _msg) override {
		switch (_level) {
			case ELogLevel::Trace:
			logger->log(spdlog::level::trace, _msg);
			break;
			case ELogLevel::Debug:
			logger->log(spdlog::level::debug, _msg);
			break;
			case ELogLevel::Info:
			logger->log(spdlog::level::info, _msg);
			break;
			case ELogLevel::Warning:
			logger->log(spdlog::level::warn, _msg);
			break;
			case ELogLevel::Error:
			logger->log(spdlog::level::err, _msg);
			break;
			case ELogLevel::Critical:
			logger->log(spdlog::level::critical, _msg);
			break;
			default:
			logger->log(spdlog::level::off, _msg);
			break;
		}
	}

private:

	//! spdlog
	std::shared_ptr<spdlog::logger> logger;

	//! Information
	std::string name;
	std::string path;
	size_t max_size;
	size_t max_files;
};

} // namespace logger
} // namespace mproject