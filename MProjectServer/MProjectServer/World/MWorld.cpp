#include "MWorld.h"
#include "Core/LogManager.h"
#include "User/MUser.h"
#include "Structure/Actor/Actor.h"

MWorld::MWorld(uint _key) :
	key(_key) {
	
}


void MWorld::JoinUser(std::weak_ptr<MUser> _user) {
	if (true == _user.expired()) {
		logger.lock()->WriteLog(ELogLevel::Info, "[MWorld::JoinUser]User is expired.");
		return;
	}

	SessionKey session_key = _user.lock()->SessionKey();
	if (true == user_map.contains(session_key)) {
		logger.lock()->WriteLog(ELogLevel::Info, "[MWorld::JoinUser]User already exists.");
		return;
	}

	user_map.emplace(session_key, _user);
	_user.lock()->SetWorld(shared_from_this());
	_user.lock()->SendTag();
	OnJoinUser(_user);
}

void MWorld::LeftUser(std::weak_ptr<MUser> _user) {
	if (true == _user.expired()) {
		logger.lock()->WriteLog(ELogLevel::Info, "[MWorld::LeftUser]User is expired.");
		return;
	}

	SessionKey session_key = _user.lock()->SessionKey();
	if (false == user_map.contains(session_key)) {
		logger.lock()->WriteLog(ELogLevel::Info, "[MWorld::LeftUser]User is not exists.");
		return;
	}

	user_map.erase(session_key);
	_user.lock()->LeftWorld();
	_user.lock()->SendTag();
	OnLeftUser(_user);
}

void MWorld::JoinActor(std::weak_ptr<Actor> _actor) {

}

void MWorld::LeftActor(std::weak_ptr<Actor> _actor) {

}

std::weak_ptr<ILogger> MWorld::GetLogger() {
	if (true == logger.expired()) {
		logger = LogManager::GetMutableInstance().GetGenericLogger();
	}
	return logger;
}
