#pragma once

#include "MProjectLogger/Core/ILogger.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"

namespace mproject {
namespace logger {

class SpdLogger final : public ILogger {
public:
	
	/*
	*	\param _name Logger name
	*	\param _path Log file path
	*	\param _max_size mb unit
	*	\param _max_files max file count (start from 1)
	*/
	SpdLogger(FString _name, FString _path, uint _max_size = 32, uint _max_files = 99) :
		name(_name),
		path(_path),
		max_size(1048576 * _max_size),
		max_files(_max_files) {
		logger = spdlog::rotating_logger_mt(name.ToString(), path.ToString(), max_size, max_files);
#ifdef _DEBUG
		logger->flush_on(spdlog::level::debug);
#else
		logger->flush_on(spdlog::level::warn);
#endif
	}

protected:
	virtual void OnWrite(ELogLevel _level, FString _msg) override {
		switch (_level) {
			case ELogLevel::Trace:		logger->log(spdlog::level::trace, _msg.data);		break;
			case ELogLevel::Debug:		logger->log(spdlog::level::debug, _msg.data);		break;
			case ELogLevel::Info:		logger->log(spdlog::level::info, _msg.data);		break;
			case ELogLevel::Warning:	logger->log(spdlog::level::warn, _msg.data);		break;
			case ELogLevel::Error:		logger->log(spdlog::level::err, _msg.data);			break;
			case ELogLevel::Critical:	logger->log(spdlog::level::critical, _msg.data);	break;
			default:					logger->log(spdlog::level::off, _msg.data);			break;
		}
	}

private:

	//! spdlog
	std::shared_ptr<spdlog::logger> logger;

	//! Information
	FString name;
	FString path;
	size_t max_size;
	uint max_files;
};

} // namespace logger
} // namespace mproject

