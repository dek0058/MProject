#include "HeadServer.h"
#include "HeadProtocolHandlerManager.h"


HeadServer::HeadServer() : NetworkServer(std::make_shared<HeadProtocolHandlerManager>()) {
}

HeadServer::~HeadServer() {

}

void HeadServer::OnAccept(std::shared_ptr<FSession> _session) {
	NetworkServer::OnAccept(_session);

	// 우선 패킷 정보 부터 보내자..
	std::vector<uint> tags;
	tags.emplace_back(MProject::Packet::Tag::Tag_Test);
	
	SendPacket(_session, GetHandlerManager()->CreateProtocolMessage(tags));

}

void HeadServer::OnConnect(std::shared_ptr<FSession> _session) {
	NetworkServer::OnConnect(_session);
	
}

void HeadServer::OnDisconnect(std::shared_ptr<FSession> _session) {
	NetworkServer::OnDisconnect(_session);
	
}


