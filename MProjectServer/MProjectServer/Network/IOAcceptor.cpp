#include "IOAcceptor.h"
#include "IOService.h"

IOAcceptor::IOAcceptor(shared_ptr<IOService> _IO_service) 
	: io_service(_IO_service->GetIOService()) {
	acceptor.reset();
}


IOAcceptor::~IOAcceptor() {
	acceptor->close();
}

void IOAcceptor::Start(const FAcceptInfo& _accept_info) {
	accept_info = _accept_info;
	asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v6(), accept_info.port_number);
	acceptor = std::make_shared<asio::ip::tcp::acceptor>(io_service, endpoint);


}

void IOAcceptor::Stop() {

}
