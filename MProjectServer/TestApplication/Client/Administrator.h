﻿/*****************************************************************//**
 * \file   Adminstrator.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-10-21
 *********************************************************************/

#pragma once

#include "Client/ServerDefine.h"
#include "Utility/TSingleton.h"

namespace mproject {

namespace logger
{
class ILogger;
enum class ELogLevel : byte;
}	// logger


class MainProcess;
class TestEngine;

class Administrator : public TSingleton<Administrator> {
public:

	/**
	 * \brief 메모리 초기화.
	 * \return 성공 여부
	 */
	bool Initialize();
	
	/**
	 * \brief 메모리 해제
	 * \return 성공 값
	 */
	int Finalize();

	/**
	 * \brief 엔진 시작
	 */
	void StartEngine();

	/**
	 * \brief 로그를 출력합니다.
	 */
	void WriteLog(logger::ELogLevel _level, FString _msg);
	void WriteLog_Trace(FString _msg);
	void WriteLog_Debug(FString _msg);
	void WriteLog_Info(FString _msg);
	void WriteLog_Warnining(FString _msg);
	void WriteLog_Error(FString _msg);
	void WriteLog_Criticial(FString _msg);

	/**
	 * \return Get server engine.
	 */
	std::weak_ptr<TestEngine> GetEngine() {
		return engine;
	}

	/**
	 * \return Get main logger.
	 */
	std::weak_ptr<logger::ILogger> GetLogger() {
		return logger;
	}
	
private:

	std::shared_ptr<logger::ILogger> logger;
	std::stop_source stop_source;

	std::shared_ptr<MainProcess> main_process;
	std::shared_ptr<TestEngine> engine;

	uint server_port;
};


}	// mproject
