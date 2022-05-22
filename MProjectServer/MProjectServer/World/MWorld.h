#pragma once
#include "Network/NetworkDefine.h"
#include "Structure/WorldStructure.h"
#include "Structure/Actor/Actor.h"

class MUser;

class MWorld {

	using UserMap = std::map<SessionKey, std::shared_ptr<MUser>>;
	using ActorMap = std::map<uint, std::shared_ptr<Actor>>;

private:

	MWorld(uint _key, EWorldType _world_type);

	void JoinUser(std::shared_ptr<MUser> _user);
	void LeftUser(std::shared_ptr<MUser> _user);

	void JoinActor(std::shared_ptr<Actor> _actor);
	void LeftActor(std::shared_ptr<Actor> _actor);


	//! Getter

	EWorldType GetWorldType() const {
		return world_type;
	}

private:

	uint key;
	EWorldType world_type;

	UserMap user_map;
	ActorMap actor_map;
};

