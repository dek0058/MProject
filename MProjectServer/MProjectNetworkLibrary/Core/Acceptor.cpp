#include "Acceptor.h"
#include "IOService.h"
#include "Session.h"


Acceptor::Acceptor(std::shared_ptr<IOService> _IO_service, ushort _port_num, uint _thread_count) :
	acceptor(_IO_service->GetIOService(), boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v6(), _port_num)),
	strand(_IO_service->GetIOService()),
	thread_count(_thread_count) {
	
}

Acceptor::~Acceptor() {
	thread_group.join_all();
}

void Acceptor::Start() {
	for (uint i = 0; i < thread_count; ++i) {
		thread_group.create_thread(boost::bind(&Acceptor::OnStart, this));
	}
}

void Acceptor::OnStart()
{
	OnAccept();
	IO_service->Run();
}

void Acceptor::OnAccept() {
	
	// 자원관리 lock잡아두던가 session을 queue를 쓰던가 하자!

	std::shared_ptr<Session> session = IO_service->GetSession();
	boost::asio::ip::tcp::socket sock(IO_service->GetIOService()); // TODO: session->GetSocket();
	
	acceptor.async_accept(
		sock,
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
