#include "HeadServer.h"
#include "HeadProtocolHandlerManager.h"


HeadServer::HeadServer() : NetworkServer(std::make_shared<HeadProtocolHandlerManager>()) {
}

HeadServer::~HeadServer() {

}
