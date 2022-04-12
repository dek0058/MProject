#pragma once

#include "Network/NetworkServer.h"
#include "Utility/TSingleton.h"

class HeadServer : public NetworkServer, public TSingleton<HeadServer> {
	//friend class TSingleton<HeadServer>;
	

public:
	HeadServer();
	~HeadServer();

private:

};
