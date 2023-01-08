#include "Acceptor.h"
#include "MProjectNetwork/Thread/ChiefThread.h"
#include "MProjectNetwork/Server/MEngine.h"
#include "MProjectNetwork/Core/IOService.h"
#include "MProjectNetwork/Core/Session.h"

#include "Exception/ExceptionUtility.h"
#include <boost/exception/diagnostic_information.hpp> 

namespace mproject {
namespace network {

Acceptor::Acceptor(
	int _fps,
	std::shared_ptr<MEngine> _server,
	ushort _port,
	boost::asio::io_service& _IO_service
)
	: EliteThread(_fps, std::static_pointer_cast<ChiefThread>(_server))
	, server (_server)
	, socket(_IO_service, EndPoint(UDP::v6(), _port), 1024, 1024, 5, server->GetLogger())
{
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

void Acceptor::OnStart() {
	__super::OnStart();
	try {
		socket.Open();
		socket.Bind();
		socket.Start();
	} catch (std::exception const& _e) {
		server->WriteLog_Error(FString(_e.what()));
	} catch (...) { //! boost
		server->WriteLog_Error(FString(boost::current_exception_diagnostic_information()));
	}
	
	server->GetIOService()->Run();
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
	socket.Close();
}

void Acceptor::OnReceiveHandler(Packet<Header> const& _packet, size_t _bytes_transferred, FPeer const& _peer) {
	GetChief()->WriteLog_Trace(pTEXT("Receive Handler"));
}

void Acceptor::OnConnectionHandler(FPeer const& _peer) {
	GetChief()->WriteLog_Trace(pTEXT("Connect Handler"));
}

void Acceptor::OnDisconnectionHandler(FPeer const& _peer) {
	GetChief()->WriteLog_Trace(pTEXT("Disconnect Handler"));
}

void Acceptor::OnTimeoutHandler(FPeer const& _peer) {
	GetChief()->WriteLog_Trace(pTEXT("Timeout Handler"));
}

}	// network
}	// mproject
