#pragma once
#include "Network/BaseProtocol.h"
#include "Network/ProtocolHandler.h"
#include "Packet/NClientActor_generated.h"

class Actor;

//! Receive
class NC2S_MoveActorInWorldProtocol : public BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(NC2S_MoveActorInWorldProtocol, MProject::Packet::Tag::Tag_C2S_MoveActorInWorld)
};
class NC2S_MoveActorInWorldHandlerHandler : public TProtocolHandler<NC2S_MoveActorInWorldProtocol> {
	virtual void OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet);
};


//! Receive
class NS2C_MoveActorInWorldProtocol : public BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(NS2C_MoveActorInWorldProtocol, MProject::Packet::Tag::Tag_S2C_MoveActorInWorld)
public:
	static std::unique_ptr<FPacket> CreatePacket(uint _world_key, std::vector<Actor> _actors);
};
class NS2C_MoveActorInWorldHandlerHandler : public TProtocolHandler<NS2C_MoveActorInWorldProtocol> {
};