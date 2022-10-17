#pragma once
/*****************************************************************//**
 * \file   TestEngine.h
 * \brief  TestEngine class
 * \details Test Server Engine.
 * 
 * \author dek0058
 * \date   2022-09-16
 * \version 0.1
 *********************************************************************/

#include "MProjectNetwork/Server/MEngine.h"

namespace mproject {

class TestEngine : public network::MEngine {

public:
	TestEngine(ushort _acceptor_port);


private:


	

};

}
