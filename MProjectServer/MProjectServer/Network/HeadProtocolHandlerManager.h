#pragma once

#include "Network/ProtocolHandler.h"

class HeadProtocolHandlerManager final : public ProtocolHandlerManager {
public:
	HeadProtocolHandlerManager() { ; }
	~HeadProtocolHandlerManager() { ; }

	void OnRegisterHandler() override { ; }

};