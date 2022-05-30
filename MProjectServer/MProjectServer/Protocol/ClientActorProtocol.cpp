#include "ClientActorProtocol.h"
#include "Manager/UserManager.h"
#include "Manager/WorldManager.h"
#include "User/MUser.h"
#include "World/MWorld.h"
#include "Core/LogManager.h"
#include "Structure/Actor/Actor.h"
#include "Structure/Player/GPC.h"


using namespace MProject;


void NC2S_MoveActorInWorldProtocolHandler::OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) {
	/*auto user = UserManager::GetMutableInstance().GetUser(_session_key);
	if (true == user.expired()) {
		GetLogger().lock()->WriteLog(ELogLevel::Warning, std::format("[NC2S_MoveActorInWorldHandler::OnReceivePacket]User not find.", _session_key));
		return;
	}

	auto data = BaseProtocol::GetData<Packet::NC2S_MoveActorInWorld>(_packet->data.data());
	auto world = WorldManager::GetMutableInstance().FindWorld(data->world_key());
	if (true == world.expired()) {
		GetLogger().lock()->WriteLog(ELogLevel::Critical, "[NC2S_MoveActorInWorldHandler::OnReceivePacket]World is not find.");
		return;
	}

	auto game_player = user.lock()->GetGamePlayer();
	if (true == game_player.expired()) {
		GetLogger().lock()->WriteLog(ELogLevel::Critical, std::format("[NC2S_MoveActorInWorldHandler::OnReceivePacket]GPC is expired. [{}]", user.lock()->GetUserKey()));
		return;
	}*/

	//for (auto iter = data->actors()->begin(); iter != data->actors()->end(); ++iter) {
	//	if (auto actor = game_player.lock()->GetActor(iter->actor_key()); false == actor.expired()) {
	//		//actor.lock()->SetTransform()
	//	}
	//}
	
	//NS2C_MoveActorInWorldProtocol::CreatePacket()
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

