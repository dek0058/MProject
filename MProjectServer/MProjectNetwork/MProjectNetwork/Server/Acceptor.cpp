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
	, endpoint(EndPoint(UDP::v6(), _port)) {
}

void Acceptor::OnStart() {

	//acceptor->async_accept()
	//acceptor->open(endpoint.protocol());

}

void Acceptor::OnUpdate() {
	if (server.expired()) {
		return;
	}

	Session* session = server.lock()->GetSession();
	if (nullptr == session) {
		throw MEXCEPTION(NullException, session);
	}

	//acceptor->async_accept()

	//Session* session = 

	//acceptor->accept()

}

void Acceptor::OnStop() {
	
}

}	// network
}	// mproject
