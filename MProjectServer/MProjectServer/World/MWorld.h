#pragma once
#include "Network/NetworkDefine.h"
#include "Structure/WorldStructure.h"
#include "Structure/Actor/Actor.h"

class MUser;

class MWorld : public std::enable_shared_from_this<MWorld> {

	using UserMap = std::map<SessionKey, std::shared_ptr<MUser>>;
	using ActorMap = std::map<uint, std::shared_ptr<Actor>>;

public:

	MWorld(uint _key);

	void JoinUser(std::shared_ptr<MUser> _user);
	void LeftUser(std::shared_ptr<MUser> _user);

	void JoinActor(std::shared_ptr<Actor> _actor);
	void LeftActor(std::shared_ptr<Actor> _actor);


	//! Getter

	uint GetWorldKey() const { return key; }

	virtual EWorldType GetWorldType() const {
		return EWorldType::None;
	}

	std::vector<uint> GetTags() const {
		return tags;
	}

protected:

	virtual void OnJoinUser(std::shared_ptr<MUser> _user) {}
	virtual void OnLeftUser(std::shared_ptr<MUser> _user) {}
	
	//! Setter
	void SetTags(std::vector<uint> _tags) {
		tags = _tags;
	}

private:

	uint key;
	UserMap user_map;
	ActorMap actor_map;
	std::vector<uint> tags;
};

