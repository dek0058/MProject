#include "IOAcceptor.h"
#include "MProjectServerDefine.h"

#include "NetworkServer.h"
#include "Session.h"

IOAcceptor::IOAcceptor(std::shared_ptr<NetworkServer> _network_server) : IOService(_network_server) {
	acceptor.reset();
}


IOAcceptor::~IOAcceptor() {
	acceptor->close();
}

void IOAcceptor::Start(const FAcceptInfo& _accept_info) {
	accept_info = _accept_info;
	asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v6(), accept_info.port_number);
	acceptor = std::make_shared<asio::ip::tcp::acceptor>(GetIOService(), endpoint);
}

void IOAcceptor::Stop() {

}

void IOAcceptor::Accept() {
	std::shared_ptr<FSession> session;
	if (false == PopSession(session)) {
		// error
		return;
	}

	/// [todo] accept
/*	acceptor->async_accept(
		GetIOService(),
		strand.wrap([this](std::shared_ptr<FSession>& _session, boost::system::error_code _error_code) {
			//std::lock_guard<std::mutex> lock(acception_mutex);
			OnAccept(_session, _error_code);
			Accept();
		})
	);
	*/
}

void IOAcceptor::OnAccept(std::shared_ptr<FSession>& _session, boost::system::error_code _error_code) {
	
}
