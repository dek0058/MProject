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

namespace logger
{
class ILogger;
}	// logger

class TestEngine : public network::MEngine {

public:
	TestEngine(ushort _acceptor_port, std::shared_ptr<logger::ILogger> _logger);


private:


	

};

}
