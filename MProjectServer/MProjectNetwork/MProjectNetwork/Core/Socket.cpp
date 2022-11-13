#include "Socket.h"
#include "MProjectNetwork/Core/IOService.h"
#include "MProjectNetwork/Server/MEngine.h"



namespace mproject {
namespace network {

Socket::Socket(
	std::shared_ptr<MEngine> _server, 
	boost::asio::ip::udp::endpoint _endpoint, 
	size_t _recv_buffer_size,
	uint _heartbeat_second /* = 5*/)
	: server(_server)
	, listening(true)
	, remote_endpoint(_endpoint)
	, recv_buffer(_recv_buffer_size)
	, heartbeat_second(_heartbeat_second) {

	/*
	timer(_server->GetIOService().lock()->Get()),
		socket(_server->GetIOService().lock()->Get()),
		*/
	HeartBeat();
}

void Socket::OnHeartBeat() {

}

void Socket::HeartBeat() {
	timer->expires_from_now(boost::posix_time::seconds(heartbeat_second));
	timer->async_wait([this](boost::system::error_code error_code) {
		OnHeartBeat();
	});
}


}	// network
}	// mproject
