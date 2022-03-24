#include "IOAcceptor.h"
#include "MProjectServerDefine.h"

#include "NetworkServer.h"

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
