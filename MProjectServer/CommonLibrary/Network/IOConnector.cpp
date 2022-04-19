#include "IOConnector.h"

#include "NetworkServer.h"

IOConnector::IOConnector(NetworkServer* _network_server) : IOService(_network_server) {

}

void IOConnector::Start(FConnectInfo const& _connect_info) {

}