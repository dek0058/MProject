#pragma once

#include "Network/NetworkServer.h"
#include "Utility/TSingleton.h"

class HeadServer : public NetworkServer, public TSingleton<HeadServer> {
	//friend class TSingleton<HeadServer>;
	

public:
	HeadServer();
	~HeadServer();

	virtual void OnAccept(std::shared_ptr<FSession> _session) override;
	virtual void OnConnect(std::shared_ptr<FSession> _session) override;
	virtual void OnDisconnect(std::shared_ptr<FSession> _session) override;

private:

};
