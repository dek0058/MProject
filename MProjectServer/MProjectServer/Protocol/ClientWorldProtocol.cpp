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

	

	MProject::Packet::NS2C_JoinUserInWorldBuilder packet_builder(builder);
	

	
	END_PACKET(packet_builder);
}


std::unique_ptr<FPacket> NS2C_LeftUserInWorldProtocol::CreatePacket(uint _world_key, std::vector<GPC> _game_players, std::vector<Actor> _actors) {
	START_PACKET(NS2C_LeftUserInWorldProtocol);

	
	
	MProject::Packet::NS2C_LeftUserInWorldBuilder packet_builder(builder);

	
	
	END_PACKET(packet_builder);
}
