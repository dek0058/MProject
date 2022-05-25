#include "ClientActorProtocol.h"
#include "Manager/UserManager.h"
#include "User/MUser.h"
#include "Structure/Actor/Actor.h"


void NC2S_MoveActorInWorldHandlerHandler::OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) {

	
}

std::unique_ptr<FPacket> NS2C_MoveActorInWorldProtocol::CreatePacket(uint _world_key, std::vector<Actor> _actors) {
	START_PACKET(NS2C_MoveActorInWorldProtocol);
	
	std::vector<flatbuffers::Offset<MProject::Packet::Actor>> actors_buf;
	for (auto actor : _actors) {
		actors_buf.emplace_back(actor.ToFaltbuffer(builder));
	}

	auto actors_data = builder.CreateVector(actors_buf);

	MProject::Packet::NS2C_MoveActorInWorldBuilder packet_builder(builder);
	packet_builder.add_world_key(_world_key);
	packet_builder.add_actors(actors_data);

	END_PACKET(packet_builder);
}
