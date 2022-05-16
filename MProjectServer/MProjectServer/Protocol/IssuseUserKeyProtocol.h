#pragma once
#include "Network/BaseProtocol.h"
#include "Network/ProtocolHandler.h"
#include "Packet/NIssuseUserKeyPacket_generated.h"

class IssuseUserKeyProtocol : public BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(IssuseUserKeyProtocol, MProject::Packet::Tag::Tag_IssueUserKey)

public:
	static std::unique_ptr<FPacket> CreatePacket(int _key) {
		START_PACKET(IssuseUserKeyProtocol);
		MProject::Packet::NIssuseUserKeyPacketBuilder packet_builder(builder);
		packet_builder.add_key(_key);
		END_PACKET(packet_builder);
	}
};

class IssuseUserKeyProtocolHandler : public TProtocolHandler<IssuseUserKeyProtocol> {
	virtual void OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet);
};
