#pragma once
#include "Actor.h"
#include "Structure/UnitStructure.h"

class UnitActor : public Actor {
public:
	FUnitData unit_data;

	UnitActor(uint _id) : Actor(_id) {}

};
