#pragma once
#include "GlobalDefine.h"
#include "Structure/PlayerStructure.h"
#include "Structure/Actor/Actor.h"
#include "Packet/Player_generated.h"

class GPC { // Game Player Controller

public:

	


private:

	std::map<EPlayerActorType, std::vector<Actor>> actor_map;
};
