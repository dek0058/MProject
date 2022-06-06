#include "WorldManager.h"
#include "Core/LogManager.h"
#include "User/MUser.h"

#pragma region World

#include "World/LoginWorld.h"
#include "World/TestWorld.h"

#pragma endregion


WorldManager::WorldManager() {
	Add<LoginWorld>();
	Add<TestWorld>();
}


void WorldManager::JoinUserToWorld(std::weak_ptr<MUser> _user, uint _world_key) {
	if (true == _user.expired()) {
		GetLogger().lock()->WriteLog(ELogLevel::Error, "[WorldManager::JoinUserToWorld] User is expired");
		return;
	}

	auto cur_world = _user.lock()->GetWorld();
	if (false == cur_world.expired()) {
		cur_world.lock()->LeftUser(_user);
	}

	auto world = FindWorld(_world_key);
	if (true == world.expired()) {
		GetLogger().lock()->WriteLog(ELogLevel::Error, "[WorldManager::JoinUserToWorld] World not found.");
		return;
	}
	
	world.lock()->JoinUser(_user);
}

void WorldManager::LeaveUserFromWorld(std::weak_ptr<MUser> _user) {
	if (true == _user.expired()) {
		GetLogger().lock()->WriteLog(ELogLevel::Error, "[WorldManager::JoinUserToWorld] User is expired");
		return;
	}
	auto cur_world = _user.lock()->GetWorld();
	if (false == cur_world.expired()) {
		cur_world.lock()->LeftUser(_user);
	}
}

std::weak_ptr<ILogger> WorldManager::GetLogger()
{
	if (true == logger.expired()) {
		logger = LogManager::GetMutableInstance().GetGenericLogger();
	}
	return logger;
}

template<typename T>
void WorldManager::Add() {
	uint key = GetWorldKey();
	world_map.emplace(key, std::static_pointer_cast<MWorld>(std::make_shared<T>(key)));
}
