#include "Session.h"
#include "IOService.h"

namespace mproject {
namespace network {

Session_TCP::Session_TCP(std::shared_ptr<IOService> _IO_service, SessionKey _session_key, ESessionType _session_type) :
	IO_Service(_IO_service),
	sock(_IO_service->GetIOService()),
	strand(_IO_service->GetIOService()),
	session_key(_session_key),
	session_type(_session_type),
	sequence_type(ESequenceType::Disconnected) {

}

Session_TCP::~Session_TCP() {
	if (IO_Service->IsRunning()) {
		Shutdown();
	}
}


void Session_TCP::Accept() {
	sequence_type = ESequenceType::Connected;

	{
		boost::asio::ip::tcp::no_delay option(true);
		GetSocket().set_option(option);
	}
}

void Session_TCP::Disconnect() {
	sequence_type = ESequenceType::Disconnected;
}

void Session_TCP::Shutdown() {
	IO_Service->GetIOService().post(
		boost::asio::bind_executor(
			strand,
			[this]() {
				if (false == GetSocket().is_open()) {
					return;
				}
				GetSocket().shutdown(boost::asio::ip::tcp::socket::shutdown_both);
				GetSocket().close();
			}
		)
	);
}

void Session_TCP::Close() {
	IO_Service->GetIOService().post(
		boost::asio::bind_executor(
			strand,
			[this]() {
				if (false == GetSocket().is_open()) {
					return;
				}
				GetSocket().close();
			}
		)
	);
}

}	// network
}	// mproject


