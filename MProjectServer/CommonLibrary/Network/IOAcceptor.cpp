#include "IOAcceptor.h"

#include "NetworkServer.h"
#include "Session.h"

IOAcceptor::IOAcceptor(NetworkServer* _network_server) : IOService(_network_server) {
	acceptor.reset();
}


IOAcceptor::~IOAcceptor() {
	acceptor->close();
}

void IOAcceptor::Start(const FAcceptInfo& _accept_info) {
	accept_info = _accept_info;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v6(), accept_info.port);
	acceptor = std::make_shared<boost::asio::ip::tcp::acceptor>(GetIOService(), endpoint);

	for (int i = 0; i < _accept_info.session_count; ++i) {
		std::shared_ptr session = std::make_shared<FSession>(
										shared_from_this(),
										accept_info.session_type,
										accept_info.send_buffer_size,
										accept_info.recv_buffer_size,
										accept_info.max_packet_size
									);
		
		StoreOwnerSesion(session);
		PushSession(session);
	}
	
	for (int i = 0; i < accept_info.thread_count; ++i) {
		Accept();
	}
	IOService::Start(accept_info.thread_count);
}

void IOAcceptor::Stop() {

}

void IOAcceptor::Accept() {
	
	std::shared_ptr<FSession> session;
	if (false == PopSession(session)) {
		// error
		return;
	}

	// 연결 대기
	session->SetSequenceType(ESequenceType::Accepting);

	acceptor->async_accept(
		session->GetSocket(),
		boost::asio::bind_executor(strand, boost::bind(&IOAcceptor::OnAccept, this, session, boost::asio::placeholders::error))
	);
}

void IOAcceptor::OnAccept(std::shared_ptr<FSession> _session, boost::system::error_code const& _error_code) {
	if (_error_code == boost::system::errc::success) {
		PushNetEvent(ENetEventType::Accepted, _session);
	} else {
		PushNetEvent(ENetEventType::Error, _session);
	}
	Accept();
}
