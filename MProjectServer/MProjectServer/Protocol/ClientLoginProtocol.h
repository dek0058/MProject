#pragma once
#include "Network/BaseProtocol.h"
#include "Network/ProtocolHandler.h"
#include "Packet/NClientLogin_generated.h"

#pragma region User Login

class NC2S_UserLoginProtocol : public BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(NC2S_UserLoginProtocol, MProject::Packet::Tag::Tag_C2S_UserLogin)
};
class NC2S_UserLoginHandlerHandler : public TProtocolHandler<NC2S_UserLoginProtocol> {
	virtual void OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet);
};


class NS2C_UserLoginProtocol : public BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(NS2C_UserLoginProtocol, MProject::Packet::Tag::Tag_S2C_UserLogin)

public:
	static std::unique_ptr<FPacket> CreatePacket(uint _key) {
		START_PACKET(NS2C_UserLoginProtocol);
		MProject::Packet::NS2C_UserLoginBuilder packet_builder(builder);
		packet_builder.add_user_key(_key);
		END_PACKET(packet_builder);
	}
};
class NS2C_UserLoginHandlerHandler : public TProtocolHandler<NS2C_UserLoginHandlerHandler> {
};

#pragma endregion
