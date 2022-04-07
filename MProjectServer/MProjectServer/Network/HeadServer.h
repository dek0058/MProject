#pragma once

#include "Network/NetworkServer.h"
#include "Utility/TSingleton.h"

class HeadServer : public NetworkServer, public TSingleton<HeadServer> {
	//HeadServer()
	~HeadServer();

public:


private:

};