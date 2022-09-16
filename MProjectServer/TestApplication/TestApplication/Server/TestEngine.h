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

class TestEngine : public mproject::network::MEngine {

public:
		
	virtual void Start() override {}

	virtual void Update() override {}

	virtual void Stop() override {}

};

}
