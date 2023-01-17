#include "LoginLevel.h"
#include "TestEngine.h"
#include "MProjectNetwork/Core/IOService.h"
#include "Exception/ExceptionUtility.h"

#include <boost/exception/diagnostic_information.hpp> 

namespace mproject {

LoginLevel::LoginLevel(
	int _fps,
	std::shared_ptr<TestEngine> _server,
	ushort _port,
	boost::asio::io_service& _IO_service,
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
{
	
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

	
}



}	// mproject
