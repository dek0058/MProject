#pragma once
#include "GlobalDefine.h"
#include "Structure/PlayerStructure.h"
#include "Structure/Actor/Actor.h"
#include "Packet/Player_generated.h"

class GPC { // Game Player Controller
public:
	
	GPC(uint _user_key) : user_key(_user_key) {}

	flatbuffers::Offset<Packet::GPC> ToFaltbuffer(flatbuffers::FlatBufferBuilder& _builder) {
		return Packet::CreateGPC(_builder, user_key);
	}

public:
	uint user_key;

	
private:
	std::map<EPlayerActorType, std::vector<Actor>> actor_map;

};
