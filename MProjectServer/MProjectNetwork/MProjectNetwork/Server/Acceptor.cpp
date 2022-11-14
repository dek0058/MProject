#include "Acceptor.h"
#include "MProjectNetwork/Thread/ChiefThread.h"
#include "MProjectNetwork/Server/MEngine.h"
#include "MProjectNetwork/Core/IOService.h"
#include "MProjectNetwork/Core/Session.h"

#include "Exception/ExceptionUtility.h"
#include <boost/system/detail/error_code.hpp>

namespace mproject {
namespace network {

Acceptor::Acceptor(int _fps, std::shared_ptr<MEngine> _server, ushort _port) 
	: EliteThread(_fps, std::static_pointer_cast<ChiefThread>(_server)),
	server (_server),
	endpoint(boost::asio::ip::tcp::v6(), _port) {
	acceptor.reset();
}

void Acceptor::OnStart() {
	if (!server.expired()) {
		auto IO_service = server.lock()->GetIOService();
		if (!IO_service) {
			acceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(IO_service->Get());
		} else {
			throw MEXCEPTION(NullException, IO_service);
		}
	} else {
		throw MEXCEPTION(ExpiredException, server);
	}
	
	if (nullptr == acceptor.get()) {
		throw MEXCEPTION(NullException, acceptor);
	}

	//acceptor->async_accept()
	//acceptor->open(endpoint.protocol());

}

void Acceptor::OnUpdate() {
	if (true == is_accepting) {
		return;
	}
	is_accepting = true;
	// Get Session....
	

	//acceptor->accept()

}

void Acceptor::OnStop() {
	boost::system::error_code error_code;
	acceptor->close(error_code);
	if (error_code != boost::system::errc::success) {
		throw boost::system::system_error(error_code);
	}
}

}	// network
}	// mproject
