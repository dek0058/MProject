#include "ClientLoginProtocol.h"
#include "Manager/UserManager.h"
#include "User/MUser.h"
#include "Core/LogManager.h"

void NC2S_UserLoginProtocolHandler::OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) {
	auto user = UserManager::GetMutableInstance().GetUser(_session_key);
	if (true == user.expired()) {
		LogManager::GetMutableInstance().GenericLog(ELogLevel::Warning, "NC2S_UserLoginHandlerHandler", "OnReceivePacket", std::format("User not find. [{}]", _session_key));
		return;
	}
	
	// TODO 유저 정보

	user.lock()->SendPacket(NS2C_UserLoginProtocol::CreatePacket(user.lock()->GetUserKey()));
}

void NC2S_UserLogoutProtocolHandler::OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) {
	auto user = UserManager::GetMutableInstance().GetUser(_session_key);
	if (true == user.expired()) {
		LogManager::GetMutableInstance().GenericLog(ELogLevel::Warning, "NC2S_UserLogoutProtocolHandler", "OnReceivePacket", std::format("User not find. [{}]", _session_key));
		return;
	}

	// TODO 유저 정보 초기화

	user.lock()->SendPacket(NS2C_UserLogoutProtocol::CreatePacket());
}
