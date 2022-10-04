#include "Acceptor.h"
#include "MProjectNetwork/Thread/ChiefThread.h"
#include "MProjectNetwork/Server/MEngine.h"

#include <boost/asio.hpp>

namespace mproject {
namespace network {

Acceptor::Acceptor(int _fps, std::shared_ptr<MEngine> _server) 
	: EliteThread(_fps, std::static_pointer_cast<ChiefThread>(_server)),
	server (_server) {
	

}

void Acceptor::OnStart() {
	
}

void Acceptor::OnUpdate() {

}

void Acceptor::OnStop() {

}

}	// network
}	// mproject
