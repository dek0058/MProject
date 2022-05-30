#pragma once
#include "Network/BaseProtocol.h"
#include "Network/ProtocolHandler.h"
#include "Packet/NClientLogin_generated.h"

#pragma region User Login

//! Receive
class NC2S_UserLoginProtocol : public BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(NC2S_UserLoginProtocol, MProject::Packet::Tag::Tag_C2S_UserLogin)
};
class NC2S_UserLoginProtocolHandler : public TProtocolHandler<NC2S_UserLoginProtocol> {
	virtual void OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet);
};

//! Send
class NS2C_UserLoginProtocol : public BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(NS2C_UserLoginProtocol, MProject::Packet::Tag::Tag_S2C_UserLogin)

public:
	static std::unique_ptr<FPacket> CreatePacket(uint _user_key) {
		START_PACKET(NS2C_UserLoginProtocol);
		MProject::Packet::NS2C_UserLoginBuilder packet_builder(builder);
		packet_builder.add_user_key(_user_key);
		END_PACKET(packet_builder);
	}
};
class NS2C_UserLoginProtocolHandler : public TProtocolHandler<NS2C_UserLoginProtocol> {
};

#pragma endregion


#pragma region User Logout

//! Receive
class NC2S_UserLogoutProtocol : public BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(NC2S_UserLogoutProtocol, MProject::Packet::Tag::Tag_C2S_UserLogout)
};
class NC2S_UserLogoutProtocolHandler : public TProtocolHandler<NC2S_UserLogoutProtocol> {
	virtual void OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet);
};

//! Send
class NS2C_UserLogoutProtocol : public BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(NS2C_UserLogoutProtocol, MProject::Packet::Tag::Tag_S2C_UserLogout)

public:
	static std::unique_ptr<FPacket> CreatePacket() {
		START_PACKET(NS2C_UserLogoutProtocol);
		MProject::Packet::NS2C_UserLogoutBuilder packet_builder(builder);
		END_PACKET(packet_builder);
	}
};
class NNS2C_UserLogoutProtocolHandler : public TProtocolHandler<NS2C_UserLogoutProtocol> {
};

#pragma endregion

