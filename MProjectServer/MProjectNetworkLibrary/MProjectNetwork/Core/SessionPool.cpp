#include "SessionPool.h"
#include "IOService.h"
#include "Session.h"

namespace mproject {
namespace network {

SessionPool_TCP::SessionPool_TCP(std::shared_ptr<IOService> _IO_service, size_t _max_size) :
    IO_service(_IO_service) {
    stores.reserve(_max_size);
}

SessionPool_TCP::~SessionPool_TCP() {
	
}

std::shared_ptr<Session_TCP> SessionPool_TCP::Get() {
	
    return std::shared_ptr<Session_TCP>();
}

void SessionPool_TCP::Release(std::shared_ptr<Session_TCP> _session) {
    if (nullptr == _session) {
        return;
    }


}


}   // network
}   // mproject

