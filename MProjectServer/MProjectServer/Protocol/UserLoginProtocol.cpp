#include "UserLoginProtocol.h"
#include "Manager/UserManager.h"
#include "User/MUser.h"
#include "Protocol/IssuseUserKeyProtocol.h"
#include "Network/HeadServer.h"


void UserLoginProtocolHandler::OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) {

	auto user = UserManager::GetMutableInstance().ConnectUser(_session_key);
	if (user == nullptr) {
		// todo error
		return;
	}

	HeadServer::GetMutableInstance().SendPacket(_session_key, std::move(IssuseUserKeyProtocol::CreatePacket(user->GetUserKey())));
}
