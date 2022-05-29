#include "LoginWorld.h"

#include "Packet/PacketTag_generated.h"
#include "Protocol/ClientLoginProtocol.h"
#include "Protocol/ClientWorldProtocol.h"

LoginWorld::LoginWorld(uint _key) : MWorld(_key) {

	SetTags({
		MProject::Packet::Tag_C2S_UserLogin,
		MProject::Packet::Tag_S2C_UserLogin,
		
		MProject::Packet::Tag_C2S_UserLogout,
		MProject::Packet::Tag_S2C_UserLogout,

		MProject::Packet::Tag_C2S_JoinWorld,
		MProject::Packet::Tag_S2C_JoinWorld,
		
		MProject::Packet::Tag_C2S_LeftWorld,
		MProject::Packet::Tag_S2C_LeftWorld,
		
		MProject::Packet::Tag_S2C_JoinUserInWorld,
		MProject::Packet::Tag_S2C_LeftUserInWorld,
		
		MProject::Packet::Tag_C2S_MoveActorInWorld,
		MProject::Packet::Tag_S2C_MoveActorInWorld
	});

}

void LoginWorld::OnJoinUser(std::shared_ptr<MUser> _user) {
	//std::unique_ptr<FPacket> packet = NS2C_JoinUserInWorlddProtocol::CreatePacket(GetWorldKey());
}

void LoginWorld::OnLeftUser(std::shared_ptr<MUser> _user) {

}
