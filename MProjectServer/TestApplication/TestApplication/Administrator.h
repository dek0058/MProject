/*****************************************************************//**
 * \file   Adminstrator.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-10-15
 *********************************************************************/

#pragma once

#include "GlobalDefine.h"
#include "Utility/TSingleton.h"

namespace mproject {

class TestEngine;

class Administrator : public TSingleton<Administrator> {

public:
	
	/**
	 * \brief 메모리 초기화.
	 * 
	 * \return 성공 여부
	 */
	bool Initialize();
	
	
	void StartServer();
	
	
	/**
	 * \brief 메모리 해제
	 */
	void Finalize();
	

private:

	std::unique_ptr<TestEngine> engine;

	uint server_port;
};


}	// mproject
