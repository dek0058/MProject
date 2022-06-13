#include "MWorld.h"
#include "Core/LogManager.h"
#include "User/MUser.h"
#include "Structure/Actor/Actor.h"

MWorld::MWorld(uint _key) :
	key(_key) {
	
}


void MWorld::JoinUser(std::weak_ptr<MUser> _user) {
	if (true == _user.expired()) {
		GetLogger().lock()->WriteLog(ELogLevel::Info, std::format("[MWorld::JoinUser]User is expired.[{}]", GetWorldKey()));
		return;
	}

	SessionKey session_key = _user.lock()->SessionKey();
	if (true == user_map.contains(session_key)) {
		GetLogger().lock()->WriteLog(ELogLevel::Info, std::format("[MWorld::JoinUser]User already exists.[{}]", GetWorldKey()));
		return;
	}

	user_map.emplace(session_key, _user);
	_user.lock()->SetWorld(shared_from_this());
	_user.lock()->SendTag();
	OnJoinUser(_user);
}

void MWorld::LeftUser(std::weak_ptr<MUser> _user) {
	if (true == _user.expired()) {
		GetLogger().lock()->WriteLog(ELogLevel::Info, std::format("[MWorld::LeftUser]User is expired.[{}]", GetWorldKey()));
		return;
	}

	SessionKey session_key = _user.lock()->SessionKey();
	if (false == user_map.contains(session_key)) {
		GetLogger().lock()->WriteLog(ELogLevel::Info, std::format("[MWorld::LeftUser]User is not exists.[{}]", GetWorldKey()));
		return;
	}

	user_map.erase(session_key);
	_user.lock()->ResetWorld();
	OnLeftUser(_user);
}

void MWorld::JoinActor(std::weak_ptr<Actor> _actor) {
	if (true == _actor.expired()) {
		GetLogger().lock()->WriteLog(ELogLevel::Info, std::format("[MWorld::JoinActor]Actor is expired.[{}]", GetWorldKey()));
		return;
	}

	uint actor_key = _actor.lock()->GetActorKey();
	if (true == actor_map.contains(actor_key)) {
		GetLogger().lock()->WriteLog(ELogLevel::Info, std::format("[MWorld::JoinActor]Actor already exists.[{}]", GetWorldKey()));
		return;
	}

	actor_map.emplace(actor_key, _actor);
}

void MWorld::LeftActor(std::weak_ptr<Actor> _actor) {
	if (true == _actor.expired()) {
		GetLogger().lock()->WriteLog(ELogLevel::Info, std::format("[MWorld::LeftActor]Actor is expired.[{}]", GetWorldKey()));
		return;
	}

	uint actor_key = _actor.lock()->GetActorKey();
	if (false == actor_map.contains(actor_key)) {
		GetLogger().lock()->WriteLog(ELogLevel::Info, std::format("[MWorld::LeftActor]Actor is not exists.[{}]", GetWorldKey()));
		return;
	}

	actor_map.erase(actor_key);
}

std::vector<std::weak_ptr<GPC>> MWorld::GetGamePlayers() const {
	std::vector<std::weak_ptr<GPC>> result;
	for (auto& user : user_map) {
		if (true == user.second.expired()) {
			continue;
		}
		result.emplace_back(user.second.lock()->GetGamePlayer());
	}
	return result;
}

std::vector<std::weak_ptr<Actor>> MWorld::GetActors() const {
	std::vector<std::weak_ptr<Actor>> result;
	for (auto& actor : actor_map) {
		result.emplace_back(std::weak_ptr<Actor>(actor.second));
	}
	return result;
}

std::weak_ptr<ILogger> MWorld::GetLogger() {
	if (true == logger.expired()) {
		logger = LogManager::GetMutableInstance().GetGenericLogger();
	}
	return logger;
}
