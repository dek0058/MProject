#pragma once
#include "IOService.h"

class NetworkServer;

class IOConnector : public IOService {
public:
	IOConnector(NetworkServer* _network_server);

	void Start(FConnectInfo const& _connect_info);

	virtual ESessionType GetSessionType() const override {
		return connect_info.session_type;
	}

private:
	FConnectInfo connect_info;

};

