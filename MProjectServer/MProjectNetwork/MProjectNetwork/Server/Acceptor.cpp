#include "Acceptor.h"
#include "MProjectNetwork/Thread/ChiefThread.h"
#include "MProjectNetwork/Server/MEngine.h"
#include "MProjectNetwork/Core/IOService.h"
#include "MProjectNetwork/Core/Session.h"

#include "Exception/ExceptionUtility.h"
#include <boost/system/detail/error_code.hpp>

namespace mproject {
namespace network {

Acceptor::Acceptor(
	int _fps,
	std::shared_ptr<MEngine> _server,
	ushort _port
)
	: EliteThread(_fps, std::static_pointer_cast<ChiefThread>(_server))
	, server (_server)
	, endpoint(EndPoint(UDP::v6(), _port))
{
}

void Acceptor::OnStart() {
	__super::OnStart();
	socket = std::make_unique<Socket<Header>>(server->GetIOService()->Get(), endpoint, 1024, 1024, 5);
	
	/*socket->SetReceiveHandler(
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
	*/
	socket->Start();
}

void Acceptor::OnUpdate() {
	__super::OnUpdate();
	Session* session = server->GetSession();
	if (nullptr == session) {
		throw MEXCEPTION(NullException, session);
	}

	//acceptor->async_accept()

	//Session* session = 

	//acceptor->accept()

}

void Acceptor::OnStop() {
	__super::OnStop();
}

void Acceptor::OnReceiveHandler(Packet<Header> const& _packet, size_t _bytes_transferred, FPeer const& _peer) {
	
}

void Acceptor::OnConnectionHandler(FPeer const& _peer) {
	
}

void Acceptor::OnDisconnectionHandler(FPeer const& _peer) {

}

void Acceptor::OnTimeoutHandler(FPeer const& _peer) {

}

}	// network
}	// mproject
