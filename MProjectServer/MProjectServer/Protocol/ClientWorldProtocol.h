#pragma once
#include "Network/BaseProtocol.h"
#include "Network/ProtocolHandler.h"
#include "Packet/NClientWorld_generated.h"


class Actor;
class GPC;

using namespace MProject;

#pragma region User Join World

//! Receive
class NC2S_JoinWorldProtocol : public BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(NC2S_JoinWorldProtocol, MProject::Packet::Tag::Tag_C2S_JoinWorld)
};
class NC2S_JoinWorldProtocolHandler : public TProtocolHandler<NC2S_JoinWorldProtocol> {
	virtual void OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet);
};

//! Send
class NS2C_JoinWorldProtocol : public BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(NS2C_JoinWorldProtocol, MProject::Packet::Tag::Tag_S2C_JoinWorld)

public:
	static std::unique_ptr<FPacket> CreatePacket(uint _world_key) {
		START_PACKET(NS2C_JoinWorldProtocol);
		MProject::Packet::NS2C_JoinWorldBuilder packet_builder(builder);
		packet_builder.add_world_key(_world_key);
		END_PACKET(packet_builder);
	}
};
class NS2C_JoinWorldProtocolHandler : public TProtocolHandler<NS2C_JoinWorldProtocol> {
};

#pragma endregion


#pragma region User Left World

//! Receive
class NC2S_LeftWorldProtocol : public BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(NC2S_LeftWorldProtocol, MProject::Packet::Tag::Tag_C2S_LeftWorld)
};
class NC2S_LeftWorldProtocolHandler : public TProtocolHandler<NC2S_LeftWorldProtocol> {
	virtual void OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet);
};


//! Send
class NS2C_LeftWorldProtocol : public BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(NS2C_LeftWorldProtocol, MProject::Packet::Tag::Tag_S2C_LeftWorld)

public:
	static std::unique_ptr<FPacket> CreatePacket() {
		START_PACKET(NS2C_LeftWorldProtocol);
		MProject::Packet::NS2C_LeftWorldBuilder packet_builder(builder);
		END_PACKET(packet_builder);
	}
};
class NS2C_LeftWorldProtocolHandler : public TProtocolHandler<NS2C_LeftWorldProtocol> {
};

#pragma endregion



#pragma region User Left World

//! Send
class NS2C_JoinUserInWorlddProtocol : public BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(NS2C_JoinUserInWorlddProtocol, MProject::Packet::Tag::Tag_S2C_JoinUserInWorld)
		
public:
	static std::unique_ptr<FPacket> CreatePacket(uint _world_key, std::vector<GPC> _game_players, std::vector<Actor> _actors);
};
class NS2C_JoinUserInWorlddProtocolHandler : public TProtocolHandler<NS2C_JoinUserInWorlddProtocol> {
};


//! Send
class NS2C_LeftUserInWorldProtocol : public BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(NS2C_LeftUserInWorldProtocol, MProject::Packet::Tag::Tag_S2C_LeftUserInWorld)

public:
	static std::unique_ptr<FPacket> CreatePacket(uint _world_key, std::vector<GPC> _game_players, std::vector<Actor> _actors);
};
class NS2C_LeftUserInWorldProtocolHandler : public TProtocolHandler<NS2C_LeftUserInWorldProtocol> {
};

#pragma endregion
