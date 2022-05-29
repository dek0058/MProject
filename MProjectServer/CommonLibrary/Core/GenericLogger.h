#pragma once
#include "ILogger.h"
#include "Utility/TSingleton.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"

using namespace spdlog;

class GenericLogger : public ILogger {
public:
	void Initailize(std::string_view _name, std::string_view _path, size_t _max_size, size_t _max_files) {
		logger = spdlog::rotating_logger_mt(_name.data(), std::format("{}/{}.log", _path, _name), _max_size, _max_files);
		logger->flush_on(spdlog::level::warn);
	}
	
	virtual void WriteLog(ELogLevel _log_level, std::string _msg) override {
		ILogger::WriteLog(_log_level, _msg);
		switch (_log_level) {
			case ELogLevel::Trace: {
				logger->log(level::trace, _msg);
				break;
			}
			case ELogLevel::Debug: {
				logger->log(level::debug, _msg);
				break;
			}
			case ELogLevel::Info: {
				logger->log(level::info, _msg);
				break;
			}
			case ELogLevel::Warning: {
				logger->log(level::warn, _msg);
				break;
			}
			case ELogLevel::Error: {
				logger->log(level::err, _msg);
				break;
			}
			case ELogLevel::Critical: {
				logger->log(level::critical, _msg);
				break;
			}
			default: {
				logger->log(level::off, _msg);
				break;
			}
		}
	}

protected:
	
	virtual void Create() override {
		Initailize("MProjectServer-logs", "MProjectServer", 65'536, 1000);
		ILogger::Create();
	}

private:
	std::shared_ptr<spdlog::logger> logger;
};
