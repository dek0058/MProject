/*****************************************************************//**
 * \file   Adminstrator.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-10-15
 *********************************************************************/

#pragma once

#include "TestApplication/ServerDefine.h"
#include "Utility/TSingleton.h"

namespace mproject {

class MainProcess;
class TestEngine;

class Administrator : public TSingleton<Administrator> {
public:

	/**
	 * \brief 메모리 초기화.
	 * 
	 * \return 성공 여부
	 */
	bool Initialize();
	
	/**
	 * \brief 메모리 해제
	 */
	void Finalize();

private:
	/**
	 * \brief UI 시작.
	 *
	 */
	void StartUI();
	
	/**
	 * \brief 서버 시작.
	 */
	void StartServer();
	

private:

	std::shared_ptr<MainProcess> main_process;

	std::shared_ptr<TestEngine> engine;

	uint server_port;
};


}	// mproject
