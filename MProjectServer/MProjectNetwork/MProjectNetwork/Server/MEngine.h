#pragma once
/*****************************************************************//**
 * \file   MEngine.h
 * \brief  MEngine class
 * \details Server core management class
 * 
 * \author dek0058
 * \date   2022-09-28
 * \version 0.2
 *********************************************************************/
#include "MProjectNetwork/NetworkDefine.h"

namespace mproject {
namespace network {

class MEngine : public std::enable_shared_from_this<MEngine> {

public:

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Stop() = 0;

	

private:
	


	// 업데이트 스레드 풀 만들어야 할듯한데
	// std::latch std::barrier
	
};

}	// network
}	// mproject
