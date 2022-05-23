#include "ClientLoginProtocol.h"
#include "Manager/UserManager.h"
#include "User/MUser.h"
#include "Network/HeadServer.h"

void NC2S_UserLoginHandlerHandler::OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) {
	auto user = UserManager::GetMutableInstance().ConnectUser(_session_key);
	if (user == nullptr) {
		// todo error
		return;
	}
	user->SendPacket(std::move(NS2C_UserLoginProtocol::CreatePacket(user->GetUserKey())));
}
