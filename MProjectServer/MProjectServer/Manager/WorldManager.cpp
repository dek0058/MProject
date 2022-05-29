#include "WorldManager.h"
#include "Core/LogManager.h"
#include "User/MUser.h"

#include "World/LoginWorld.h"

WorldManager::WorldManager() {

	Add<LoginWorld>();
}


void WorldManager::JoinUserToWorld(std::shared_ptr<MUser> _user, uint _world_key) {
	
	auto cur_world = _user->GetWorld();
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

template<typename T>
void WorldManager::Add() {
	uint key = GetWorldKey();
	world_map.emplace(key, std::static_pointer_cast<MWorld>(std::make_shared<T>(key)));
}
