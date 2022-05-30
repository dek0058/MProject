#include "ProtocolHandler.h"
#include "BaseProtocol.h"
#include "Session.h"
#include "Utility/UniversalToolkit.h"
#include "Core/LogManager.h"

template<typename Protocol>
std::weak_ptr<ILogger> TProtocolHandler<Protocol>::GetLogger() {
	if (true == logger.expired()) {
		logger = LogManager::GetMutableInstance().GetGenericLogger();
	}
	return logger;
}


void ProtocolHandlerManager::ReceivePacket(std::shared_ptr<FSession> _session, std::unique_ptr<FPacket> _packet) {
	SessionKey session_key = _session->GetSessionKey();
	std::string hash_key = UniversalToolkit::Digest2Hex(_packet->hash_code);
	if (handler_map.find(hash_key) == handler_map.end()) {
		throw std::runtime_error("ProtocolHandlerManager::ReceivePacket: no handler for hash_key: " + hash_key);
	}
	handler_map[hash_key]->ReceivePacket(session_key, std::move(_packet));
}

std::unique_ptr<FPacket> ProtocolHandlerManager::CreateProtocolMessage(std::vector<uint> _tags)
{
	std::vector<std::tuple<uint, std::vector<byte>>> protocol_array;
	protocol_array.reserve(_tags.size());
	for (auto& tag : _tags) {
		if (true == handler_tag_map.contains(tag))
		{
			protocol_array.push_back({ tag, handler_tag_map[tag]->GetHashCode() });
		}
	}
	return std::move(ProtocolMessage::CreatePacket(protocol_array));
}
