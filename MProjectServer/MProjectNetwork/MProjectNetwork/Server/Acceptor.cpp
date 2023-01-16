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
	size_t _max_session_count,
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
	, session_queue(_max_session_count)
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

	if (false == socket.IsListening()) {
		return;
	}
	Session** ptr_session = session_queue.front();
	if (nullptr == ptr_session) {
		return;
	}
	server->ConnectSession((*ptr_session));
	session_queue.pop();
}

void Acceptor::OnStop() {
	__super::OnStop();
	socket.Close();

	Session** ptr_session = nullptr;
	do {
		ptr_session = session_queue.front();
		if (nullptr != ptr_session) {
			server->ReleaseSession((*ptr_session));
			session_queue.pop();
		}
	} while (ptr_session == nullptr);
}

void Acceptor::OnConnectionHandler(FPeer const& _peer) {
	Session* session = server->GetSession();
	try {
		if (nullptr == session) {
			throw MEXCEPTION(NullException, session);
		}

		// TODO: Session Settings...
		session->SetAddress(_peer.endpoint.address());

		if (!session_queue.try_emplace(session)) {	// 대기열이 가득 찼다.
			PacketMessage<Header> message(socket.Self().uuid, packet_message::DISCONNECTION_TYPE);
			socket.AsyncSendTo(reinterpret_cast<void**>(&message), sizeof(message), _peer.endpoint);
			server->ReleaseSession(session);
			return;
		}
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

}	// network
}	// mproject
