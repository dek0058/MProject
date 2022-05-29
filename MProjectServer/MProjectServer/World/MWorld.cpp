#include "MWorld.h"
#include "Core/LogManager.h"
#include "User/MUser.h"

MWorld::MWorld(uint _key) :
	key(_key) {
	
}


void MWorld::JoinUser(std::shared_ptr<MUser> _user) {
	if (_user.get() == nullptr) {
		LogManager::GetMutableInstance().GenericLog(ELogLevel::Info, "MWorld", "JoinUser", "User is null");
		return;
	}

	if (user_map.contains(_user->SessionKey())) {
		LogManager::GetMutableInstance().GenericLog(ELogLevel::Info, "MWorld", "JoinUser", "User is null");
		return;
	}

	user_map.emplace(_user->SessionKey(), _user);
	_user->SetWorld(shared_from_this());
	_user->SendTag();
	OnJoinUser(_user);
}

void MWorld::LeftUser(std::shared_ptr<MUser> _user) {
	if (_user.get() == nullptr) {
		LogManager::GetMutableInstance().GenericLog(ELogLevel::Info, "MWorld", "LeftUser", "User is null");
		return;
	}

	if (!user_map.contains(_user->SessionKey())) {
		LogManager::GetMutableInstance().GenericLog(ELogLevel::Info, "MWorld", "LeftUser", "User is null");
		return;
	}

	user_map.erase(_user->SessionKey());
	_user->LeftWorld();
	_user->SendTag();
	OnLeftUser(_user);
}

void MWorld::JoinActor(std::shared_ptr<Actor> _actor) {

}

void MWorld::LeftActor(std::shared_ptr<Actor> _actor) {

}
