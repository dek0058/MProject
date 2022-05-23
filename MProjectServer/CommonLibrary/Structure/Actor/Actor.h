#pragma once
#include "GlobalDefine.h"
#include "Structure/Core/Transform.h"

class Actor {
public:
	uint actor_key;
	FTransform transform;


	Actor(uint _actor_key) : actor_key(_actor_key) {}


};
