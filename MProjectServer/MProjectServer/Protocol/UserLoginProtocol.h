#pragma once
#include "Network/BaseProtocol.h"
#include "Network/ProtocolHandler.h"
#include "Packet/NUserLoginPacket_generated.h"

class UserLoginProtocol : public BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(UserLoginProtocol, MProject::Packet::Tag::Tag_UserLogin)

public:
	static std::unique_ptr<FPacket> CreatePacket() {
		START_PACKET(UserLoginProtocol);
		MProject::Packet::NUserLoginPacketBuilder packet_builder(builder);
		END_PACKET(packet_builder);
	}
};

class UserLoginProtocolHandler : public TProtocolHandler<UserLoginProtocol> {
	virtual void OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet);
};
