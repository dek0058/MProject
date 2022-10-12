﻿#include "Acceptor.h"
#include "MProjectNetwork/Thread/ChiefThread.h"
#include "MProjectNetwork/Server/MEngine.h"
#include "MProjectNetwork/Core/IOService.h"
#include "MProjectNetwork/Core/Session.h"

#include "Exception/ExpiredException.h"

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
		if (!IO_service.expired()) {
			acceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(IO_service.lock()->Get());
		} else {
			throw ExpiredException("IO_service", __LINE__, __FILE__);
		}
	} else {
		throw ExpiredException("server", __LINE__, __FILE__);
	}
	
	if (nullptr == acceptor.get()) {
		
	}

}

void Acceptor::OnUpdate() {

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
