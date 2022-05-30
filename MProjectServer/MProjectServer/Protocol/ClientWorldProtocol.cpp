#include "ClientWorldProtocol.h"
#include "Manager/UserManager.h"
#include "Manager/WorldManager.h"
#include "User/MUser.h"
#include "Core/ILogger.h"
#include "Structure/Actor/Actor.h"
#include "Structure/Player/GPC.h"

#include "World/TestWorld.h"
#include "World/LoginWorld.h"

void NC2S_JoinWorldProtocolHandler::OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) {
	auto user = UserManager::GetMutableInstance().GetUser(_session_key);
	if (true == user.expired()) {
		GetLogger().lock()->WriteLog(ELogLevel::Warning, std::format("[NC2S_JoinWorldHandlerHandler::OnReceivePacket]User not find.", _session_key));
		return;
	}

	auto world = WorldManager::GetMutableInstance().FindWorld<TestWorld>();
	if (true == world.expired()) {
		GetLogger().lock()->WriteLog(ELogLevel::Critical, "[NC2S_JoinWorldHandlerHandler::OnReceivePacket]Test World is not find.");
		return;
	}

	WorldManager::GetMutableInstance().JoinUserToWorld(user, world.lock()->GetWorldKey());
	user.lock()->SendPacket(NS2C_JoinWorldProtocol::CreatePacket(world.lock()->GetWorldKey()));
}


void NC2S_LeftWorldProtocolHandler::OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) {
	auto user = UserManager::GetMutableInstance().GetUser(_session_key);
	if (true == user.expired()) {
		GetLogger().lock()->WriteLog(ELogLevel::Warning, std::format("[NC2S_LeftWorldHandlerHandler::OnReceivePacket]User not find.", _session_key));
		return;
	}

	auto world = WorldManager::GetMutableInstance().FindWorld<LoginWorld>();
	if (true == world.expired()) {
		GetLogger().lock()->WriteLog(ELogLevel::Critical, "[NC2S_LeftWorldHandlerHandler::OnReceivePacket]Test World is not find.");
		return;
	}

	WorldManager::GetMutableInstance().JoinUserToWorld(user, world.lock()->GetWorldKey());
	user.lock()->SendPacket(NS2C_LeftWorldProtocol::CreatePacket());
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
