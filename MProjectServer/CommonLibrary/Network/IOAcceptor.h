#pragma once
#include "IOService.h"

using namespace boost;

class NetworkServer;

class IOAcceptor : public IOService {

public:

	IOAcceptor(std::shared_ptr<NetworkServer> _network_server);
	~IOAcceptor();

	void Start(const FAcceptInfo& _accept_info);
	void Stop();

	virtual ESessionType GetSessionType() const override {
		return accept_info.session_type;
	}

private:

	FAcceptInfo accept_info;
	std::shared_ptr<asio::ip::tcp::acceptor> acceptor;
};
