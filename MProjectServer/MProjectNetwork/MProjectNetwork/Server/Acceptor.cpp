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
	boost::asio::io_service& _IO_service,
	size_t _receive_packet_capacity,
	size_t _max_packet_size,
	decimal _heartbeat_second
)
	: EliteThread(_fps, std::static_pointer_cast<ChiefThread>(_server))
	, server (_server)
	, socket(
		_IO_service, 
		EndPoint(UDP::v6(), _port), 
		_receive_packet_capacity, 
		_max_packet_size, 
		_heartbeat_second, 
		server->GetLogger()
	)
{
	socket.SetConnectionHandler(
		[this](FPeer const& _peer) {
			OnConnectionHandler(_peer);
		}
	);
}

void Acceptor::OnStart() {
	__super::OnStart();
	try {
		socket.Open();
		socket.Bind();
		socket.Start();
	} catch (BaseException const _me) {
		server->WriteLog_Error(FString(_me.What()));
	} catch (std::exception const& _e) {
		server->WriteLog_Error(FString(_e.what()));
	} catch (...) { //! boost
		server->WriteLog_Error(FString(boost::current_exception_diagnostic_information()));
	}
	
	server->GetIOService()->Run();
}

void Acceptor::OnUpdate() {
	__super::OnUpdate();
	//Session* session = server->GetSession();
	//if (nullptr == session) {
	//	throw MEXCEPTION(NullException, session);
	//}

	//acceptor->async_accept()

	//Session* session = 

	//acceptor->accept()

}

void Acceptor::OnStop() {
	__super::OnStop();
	socket.Close();
}

void Acceptor::OnConnectionHandler(FPeer const& _peer) {
	GetChief()->WriteLog_Trace(pTEXT("Connect Handler"));
	Session* session = server->GetSession();
	if (nullptr == session) {
		throw MEXCEPTION(NullException, session);
	}
	//server->ConnectSession(session);
	//// TODO:
}

}	// network
}	// mproject
