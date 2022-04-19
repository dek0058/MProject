#pragma once
#include "IOService.h"


class NetworkServer;
struct FSession;

class IOAcceptor : public IOService {

public:

	IOAcceptor(NetworkServer* _network_server);
	~IOAcceptor();

	void Start(const FAcceptInfo& _accept_info);
	void Stop();

	void Accept();

	virtual ESessionType GetSessionType() const override {
		return accept_info.session_type;
	}

private:
	void OnAccept(std::shared_ptr<FSession> _session, boost::system::error_code const& _error_code);

private:

	FAcceptInfo accept_info;
	std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor;
	//mutable std::mutex acception_mutex;
};
