#include "Session.h"

namespace mproject {
namespace network {


Session::Session(
	boost::asio::io_service& _IO_service,
	EndPoint _endpoint,
	size_t _receive_packet_capacity,
	size_t _max_packet_size,
	decimal _heartbeat_second
)
	: socket(_IO_service, _endpoint, _receive_packet_capacity, _max_packet_size, _heartbeat_second)
	, session_key(0)
{
	BindHandler();
}

Session::Session(
	boost::asio::io_service& _IO_service,
	size_t _receive_packet_capacity,
	size_t _max_packet_size,
	decimal _heartbeat_second
)
	: socket(_IO_service, _receive_packet_capacity, _max_packet_size, _heartbeat_second)
	, session_key(0)
{
	BindHandler();
}

void Session::BindHandler() {
	socket.SetReceiveHandler(
		[this](Packet<Header> const& _packet, size_t _bytes_transferred, FPeer const& _peer) {
			OnReceiveHandler(_packet, _bytes_transferred, _peer);
		}
	);
	
	socket.SetConnectionHandler(
		[this](FPeer const& _peer) {
			OnConnectionHandler(_peer);
		}
	);
	
	socket.SetDisconnectionHandler(
		[this](FPeer const& _peer) {
			OnDisconnectionHandler(_peer);
		}
	);
	
	socket.SetTimeoutHandler(
		[this](FPeer const& _peer) {
			OnTimeoutHandler(_peer);
		}
	);
}

void Session::OnReceiveHandler(Packet<Header> const& _packet, size_t _bytes_transferred, FPeer const& _peer) {
	
}

void Session::OnConnectionHandler(FPeer const& _peer) {

}

void Session::OnDisconnectionHandler(FPeer const& _peer) {

}

void Session::OnTimeoutHandler(FPeer const& _peer) {
	
}







}	// network
}	// mproject

