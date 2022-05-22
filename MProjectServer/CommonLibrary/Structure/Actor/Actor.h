#pragma once
#include "GlobalDefine.h"
#include "Structure/Core/Transform.h"

class Actor {
public:
	uint id;
	FTransform transform;


	Actor(uint _id) : id(_id) {}


};
