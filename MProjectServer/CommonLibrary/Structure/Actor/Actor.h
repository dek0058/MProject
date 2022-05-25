#pragma once
#include "GlobalDefine.h"
#include "Structure/Core/Transform.h"
#include "Packet/Actor_generated.h"

class Actor {

public:

	Actor(uint _actor_key, uint _user_Key) : actor_key(_actor_key), user_key(_user_Key) {
	}

	flatbuffers::Offset<Packet::Actor> ToFaltbuffer(flatbuffers::FlatBufferBuilder& _builder) {
		return Packet::CreateActor(_builder, actor_key, user_key, transform.ToFaltbuffer(_builder));
	}



	
public:
	uint actor_key;
	uint user_key;
	FTransform transform;

};
