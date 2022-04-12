#include "HeadServer.h"
#include "HeadProtocolHandlerManager.h"


HeadServer::HeadServer() : NetworkServer(std::make_unique<HeadProtocolHandlerManager>()) {
}

HeadServer::~HeadServer() {

}
