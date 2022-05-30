#pragma once
#include "GlobalDefine.h"
#include "Core/LogManager.h"
#include "Structure/PlayerStructure.h"
#include "Packet/Player_generated.h"

using namespace MProject;

class Actor;

class GPC : public std::enable_shared_from_this<GPC> { // Game Player Controller
public:
	
	GPC(uint _user_key) : user_key(_user_key) {}

	void TakeActor(std::shared_ptr<Actor> _actor);
	void LostActor(uint _actor_key);

	//! Getter

	flatbuffers::Offset<Packet::GPC> ToFaltbuffer(flatbuffers::FlatBufferBuilder& _builder) {
		return Packet::CreateGPC(_builder, GetUserKey());
	}

	uint GetUserKey() const {
		return user_key;
	}

	std::weak_ptr<Actor> GetActor(uint _actor_key) {
		if (false == actor_map.contains(_actor_key)) {
			return std::weak_ptr<Actor>();
		} else {
			return std::weak_ptr<Actor>(actor_map[_actor_key]);
		}
	}

private:
	uint user_key;
	std::map<uint, std::shared_ptr<Actor>> actor_map;

};
