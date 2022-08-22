#include "Acceptor.h"
#include "IOService.h"
#include "Session.h"
#include "SessionObserver.h"


Acceptor::Acceptor(std::shared_ptr<IOService> _IO_service, std::shared_ptr<SessionObserver> _session_observer, ushort _port_num, uint _thread_count) :
	acceptor(_IO_service->GetIOService(), boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v6(), _port_num)),
	strand(_IO_service->GetIOService()),
	thread_count(_thread_count),
	session_ob(_session_observer) {
	
}

Acceptor::~Acceptor() {
	thread_group.join_all();
}

void Acceptor::Start() {
	for (uint i = 0; i < thread_count; ++i) {
		thread_group.create_thread(boost::bind(&Acceptor::OnStart, this));
	}
}

void Acceptor::OnStart() {
	OnAccept();
	IO_service->Run();
}

void Acceptor::OnAccept() {
	std::shared_ptr<Session> session = session_ob->GetSession();
	
	acceptor.async_accept(
		session->GetSocket(),
		boost::asio::bind_executor(
			strand,
			boost::bind(&Acceptor::PostAccept, this, session, boost::asio::placeholders::error
			)
		)
	);
}

void Acceptor::PostAccept(std::shared_ptr<Session> _session, boost::system::error_code const& _ec) {
	OnAccept();
}
