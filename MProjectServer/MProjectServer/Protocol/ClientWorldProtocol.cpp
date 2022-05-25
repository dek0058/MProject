#include "ClientWorldProtocol.h"
#include "Manager/UserManager.h"
#include "User/MUser.h"
#include "Structure/Actor/Actor.h"
#include "Structure/Player/GPC.h"

void NC2S_JoinWorldHandlerHandler::OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) {

}


void NC2S_LeftWorldHandlerHandler::OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) {
	
}


std::unique_ptr<FPacket> NS2C_JoinUserInWorlddProtocol::CreatePacket(uint _world_key, std::vector<GPC> _game_players, std::vector<Actor> _actors) {
	START_PACKET(NS2C_JoinUserInWorlddProtocol);

	std::vector<flatbuffers::Offset<MProject::Packet::GPC>> game_palyers_buf;
	for (auto game_player : _game_players) {
		game_palyers_buf.emplace_back(game_player.ToFaltbuffer(builder));
	}

	std::vector<flatbuffers::Offset<MProject::Packet::Actor>> actors_buf;
	for (auto actor : _actors) {
		actors_buf.emplace_back(actor.ToFaltbuffer(builder));
	}

	auto game_player_data = builder.CreateVector(game_palyers_buf);
	auto actors_data = builder.CreateVector(actors_buf);

	MProject::Packet::NS2C_JoinUserInWorldBuilder packet_builder(builder);
	packet_builder.add_world_key(_world_key);
	packet_builder.add_players(game_player_data);
	packet_builder.add_actors(actors_data);
	
	END_PACKET(packet_builder);
}


std::unique_ptr<FPacket> NS2C_LeftUserInWorldProtocol::CreatePacket(uint _world_key, std::vector<GPC> _game_players, std::vector<Actor> _actors) {
	START_PACKET(NS2C_LeftUserInWorldProtocol);

	std::vector<flatbuffers::Offset<MProject::Packet::GPC>> game_palyers_buf;
	for (auto game_player : _game_players) {
		game_palyers_buf.emplace_back(game_player.ToFaltbuffer(builder));
	}

	std::vector<flatbuffers::Offset<MProject::Packet::Actor>> actors_buf;
	for (auto actor : _actors) {
		actors_buf.emplace_back(actor.ToFaltbuffer(builder));
	}

	auto game_player_data = builder.CreateVector(game_palyers_buf);
	auto actors_data = builder.CreateVector(actors_buf);

	MProject::Packet::NS2C_LeftUserInWorldBuilder packet_builder(builder);
	packet_builder.add_world_key(_world_key);
	packet_builder.add_players(game_player_data);
	packet_builder.add_actors(actors_data);
	
	END_PACKET(packet_builder);
}
