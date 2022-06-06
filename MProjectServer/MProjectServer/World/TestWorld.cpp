#include "TestWorld.h"
#include "Packet/PacketTag_generated.h"
#include "Protocol/ClientWorldProtocol.h"
#include "Protocol/ClientActorProtocol.h"

TestWorld::TestWorld(uint _key) : MWorld(_key) {
	SetTags({
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

void TestWorld::OnJoinUser(std::weak_ptr<MUser> _user) {

}

void TestWorld::OnLeftUser(std::weak_ptr<MUser> _user) {

}
