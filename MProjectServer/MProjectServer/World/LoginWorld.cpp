#include "LoginWorld.h"
#include "User/MUser.h"

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
	});

}

void LoginWorld::OnJoinUser(std::weak_ptr<MUser> _user) {
	if (true == _user.expired()) {
		logger.lock()->WriteLog(ELogLevel::Info, "[LoginWorld::OnJoinUser]User is expired.");
		return;
	}
	//_user.lock()->SendPacket(NS2C_JoinUserInWorlddProtocol::CreatePacket(GetWorldKey(), ));
}

void LoginWorld::OnLeftUser(std::weak_ptr<MUser> _user) {
	
	

}
