#pragma once
#include "Network/NetworkDefine.h"
#include "Structure/WorldStructure.h"
#include "Structure/Actor/Actor.h"

class MUser;
class Actor;
class ILogger;
class GPC;

class MWorld : public std::enable_shared_from_this<MWorld> {

	using UserMap = std::map<uint, std::weak_ptr<MUser>>;
	using ActorMap = std::map<uint, std::shared_ptr<Actor>>;

public:

	MWorld(uint _key);

	void JoinUser(std::weak_ptr<MUser> _user);
	
	void LeftUser(std::weak_ptr<MUser> _user);

	void JoinActor(std::weak_ptr<Actor> _actor);
	void JoinActor(std::vector<std::weak_ptr<Actor>> _actors);

	void LeftActor(std::weak_ptr<Actor> _actor);
	void LeftActor(std::vector<std::weak_ptr<Actor>> _actors);


	//! Getter

	uint GetWorldKey() const { return key; }

	virtual EWorldType GetWorldType() const {
		return EWorldType::None;
	}

	std::vector<uint> GetTags() const {
		return tags;
	}

	std::vector<std::weak_ptr<GPC>> GetGamePlayers() const;
	std::vector<std::weak_ptr<Actor>> GetActors() const;

	//! Broadcast Alter
	void Send_JoinActor(std::weak_ptr<Actor> _actor);
	void Send_JoinActor(std::vector<std::weak_ptr<Actor>> _actors);

protected:

	virtual void OnJoinUser(std::weak_ptr<MUser> _user) {}
	virtual void OnLeftUser(std::weak_ptr<MUser> _user) {}
	
	//! Setter
	void SetTags(std::vector<uint> _tags) {
		tags = _tags;
	}

protected:
	
	//! Getter

	std::weak_ptr<ILogger> logger;
	std::weak_ptr<ILogger> GetLogger();

private:

	uint key;
	UserMap user_map;
	ActorMap actor_map;
	std::vector<uint> tags;

};

