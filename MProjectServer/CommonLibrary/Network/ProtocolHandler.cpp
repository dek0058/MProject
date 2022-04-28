#include "ProtocolHandler.h"
#include "BaseProtocol.h"
#include "Session.h"
#include "Utility/UniversalToolkit.h"

void ProtocolHandlerManager::SendPacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) {

}

void ProtocolHandlerManager::ReceivePacket(std::shared_ptr<FSession> _session, std::unique_ptr<FPacket> _packet) {
	SessionKey session_key = _session->GetSessionKey();
	std::string hash_key = UniversalToolkit::Digest2Hex(_packet->hash_code);
	if (handler_map.find(hash_key) == handler_map.end()) {
		throw std::runtime_error("ProtocolHandlerManager::ReceivePacket: no handler for hash_key: " + hash_key);
	}
	handler_map[hash_key]->ReceivePacket(session_key, std::move(_packet));
}
