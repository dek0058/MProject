#include "ProtocolHandler.h"
#include "BaseProtocol.h"
#include "Session.h"

void ProtocolHandlerManager::SendPacket(SessionKey _session_key, FPacket* _protocol) {

}

void ProtocolHandlerManager::ReceivePacket(std::shared_ptr<FSession> _session, std::unique_ptr<byte[]> _data) {
	SessionKey session_key = _session->GetSessionKey();

	//std::string hash_key;

	//handler_map[hash_key]->ReceivePacket(session_key);
}
