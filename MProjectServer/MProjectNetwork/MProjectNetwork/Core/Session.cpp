#include "Session.h"
#include "IOService.h"
#include "SessionPool.h"

namespace mproject {
namespace network {

//! Session
Session::Session(std::shared_ptr<IOService> _IO_service, ESessionType _session_type) :
	IO_Service(_IO_service),
	session_key(0),
	session_type(_session_type),
	sequence_type(ESequenceType::Disconnected) {

	session_pool.reset();
}

Session::~Session() {
	if (!session_pool.expired()) {
		session_pool.lock()->Release(shared_from_this());
	}
}

void Session::SetParent(std::weak_ptr<SessionPool> _session_pool) {
	session_pool = _session_pool;
}

//! Session_TCP
Session_TCP::Session_TCP(std::shared_ptr<IOService> _IO_service, ESessionType _session_type) : 
	Session(_IO_service, _session_type),
	sock(_IO_service->GetIOService()),
	strand(_IO_service->GetIOService()) {
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


