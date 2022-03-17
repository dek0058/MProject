#pragma once

#include "NetworkDefine.h"

class IOService;

class NetworkServer {
public:

	NetworkServer();


private:
	
	std::vector<std::shared_ptr<IOService>> IO_service_vector;

};
