#include "LoginLevel.h"
#include "TestEngine.h"
#include "MProjectNetwork/Core/IOService.h"
#include "MProjectNetwork/Core/Session.h"
#include "Exception/ExceptionUtility.h"

#include <boost/exception/diagnostic_information.hpp> 

namespace mproject {

LoginLevel::LoginLevel(
	int _fps,
	std::shared_ptr<TestEngine> _server,
	ushort _port,
	boost::asio::io_service& _IO_service,
	size_t _session_count,
	size_t _receive_packet_capacity,
	size_t _max_packet_size,
	decimal _heartbeat_second
)
	: network::EliteThread(_fps, std::static_pointer_cast<network::ChiefThread>(_server))
	, server(_server)
	, socket(
		_IO_service,
		network::EndPoint(network::UDP::v6(), _port),
		_receive_packet_capacity,
		_max_packet_size,
		_heartbeat_second,
		_server->GetLogger()
	)
	, session_count(_session_count)
{
	//peer_key_set.reserve(_session_count);
	//
	//socket.SetReceiveHandler([this](auto _packet, auto _bytes_transferred, auto _peer) {
	//	OnReceive(_packet, _bytes_transferred, _peer);
	//});
	//
	//socket.SetConnectionHandler([this](auto _peer) {
	//	OnConnection(_peer);
	//});
	//
	//socket.SetDisconnectionHandler([this](auto _peer) {
	//	OnDisconnection(_peer);
	//});
	//
	//socket.SetTimeoutHandler([this](auto _peer) {
	//	OnDisconnection(_peer);
	//});
	
}

void LoginLevel::OnStart() {
	__super::OnStart();

	try {
		socket.Open();
		socket.Bind();
		socket.Start();
	}
	catch (BaseException const _me) {
		server->WriteLog_Error(FString(_me.What()));
	}
	catch (std::exception const& _e) {
		server->WriteLog_Error(FString(_e.what()));
	}
	catch (...) { //! boost
		server->WriteLog_Error(FString(boost::current_exception_diagnostic_information()));
	}
}

void LoginLevel::OnUpdate() {
	__super::OnUpdate();

	
}

void LoginLevel::OnStop() {
	__super::OnStop();
	socket.Close();

	//network::Session** ptr_session = nullptr;
	//do {
	//	ptr_session = session_queue.front();
	//	if (nullptr != ptr_session) {
	//		server->ReleaseSession((*ptr_session));
	//		session_queue.pop();
	//	}
	//} while (ptr_session == nullptr);
}

void LoginLevel::OnReceive(network::Packet<Header> const& _packet, size_t _bytes_transferred, network::FPeer const& _peer) {
	
	
	

}

void LoginLevel::OnConnection(network::FPeer const& _peer) {
	//if (peer_key_set.contains(_peer.uuid)) {
	//	return;
	//}



}

void LoginLevel::OnDisconnection(network::FPeer const& _peer) {
	//if (!peer_key_set.contains(_peer.uuid)) {
	//	return;
	//}

}

}	// mproject
