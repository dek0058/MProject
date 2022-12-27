#include "Session.h"



namespace mproject {
namespace network {

Session::Session() {


	socket->SetReceiveHandler(
		[this](Packet<Header> const& _packet, size_t _bytes_transferred, FPeer const& _peer) {
			OnReceiveHandler(_packet, _bytes_transferred, _peer);
		}
	);

	socket->SetConnectionHandler(
		[this](FPeer const& _peer) {
			OnConnectionHandler(_peer);
		}
	);

	socket->SetDisconnectionHandler(
		[this](FPeer const& _peer) {
			OnDisconnectionHandler(_peer);
		}
	);

	socket->SetTimeoutHandler(
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

