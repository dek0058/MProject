#include "Socket.h"
#include "MProjectNetwork/Core/IOService.h"
#include "MProjectNetwork/Server/MEngine.h"



namespace mproject {
namespace network {

Socket::Socket(std::shared_ptr<MEngine> _server, boost::asio::ip::udp::endpoint _endpoint, size_t _recv_buffer_size)
	: server(_server), 
	  timer(_server->GetIOService().lock()->Get()),
	  socket(_server->GetIOService().lock()->Get()), 
	  listening(true),
	  remote_endpoint(_endpoint), 
	  recv_buffer(_recv_buffer_size) {
	
	OnKeepAlive();
}

void Socket::OnKeepAliveCheck() {

}

void Socket::OnKeepAlive() {
	timer.expires_from_now(boost::posix_time::seconds(3));
	timer.async_wait([this](boost::system::error_code error_code) {
		this->OnKeepAliveCheck();
	});
}


}	// network
}	// mproject
