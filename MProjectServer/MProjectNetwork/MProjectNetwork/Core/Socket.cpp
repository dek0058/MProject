#include "Socket.h"
#include "MProjectNetwork/Core/IOService.h"
#include "MProjectNetwork/Server/MEngine.h"
#include "Exception/ExceptionUtility.h"


namespace mproject {
namespace network {

Socket::Socket(
	std::shared_ptr<MEngine> _server, 
	EndPoint _endpoint,
	size_t _recv_buffer_size,
	uint _heartbeat_second /* = 5*/)
	: server(_server)
	, listening(true)
	, remote_endpoint(_endpoint)
	, recv_buffer(_recv_buffer_size)
	, heartbeat_second(_heartbeat_second) {

	if (true == server.expired())
	{
		throw MEXCEPTION(ExpiredException, sever);
	}
	std::shared_ptr<MEngine> server_ptr = server.lock();

	IO_service = server_ptr->GetIOService();
	if (true == IO_service.expired())
	{
		throw MEXCEPTION(ExpiredException, IO_service);
	}
	std::shared_ptr<IOService> IO_service_ptr = IO_service.lock();

	socket = std::make_optional<UDP_Scoket>(IO_service_ptr->Get());
	timer = std::make_optional<boost::asio::deadline_timer>(IO_service_ptr->Get());

	/*
	timer(_server->GetIOService().lock()->Get()),
		socket(_server->GetIOService().lock()->Get()),
		*/
	HeartBeat();
}

void Socket::Close() noexcept {
	// TODO:
	listening = false;
}

void Socket::Connect(EndPoint& _endpoint) {
	
}

void Socket::OnHeartBeat() {
	
	std::chrono::seconds now = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());

	// TODO: peer

	if (listening) {
		// TODO
		HeartBeat();
	}

}

void Socket::HeartBeat() {
	timer->expires_from_now(boost::posix_time::seconds(heartbeat_second));
	timer->async_wait([this](boost::system::error_code const& _error_code) {
		if (_error_code == boost::system::errc::success)
		{
			// TODO:연결 끊기
			return;
		}

		OnHeartBeat();
	});
}

}	// network
}	// mproject
