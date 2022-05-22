#pragma once
#include "Network/NetworkDefine.h"
#include "Utility/TSingleton.h"
#include "Structure/WorldStructure.h"
#include "World/MWorld.h"

struct FSession;


class WorldManager : public TSingleton<WorldManager> {
	
	using WorldMap = std::map<EWorldType, std::shared_ptr<MWorld>>();

	static int GetWorldKey() {
		static int key = 0;
		return ++key;
	}

public:

	
private:
	
	
	WorldMap world_map;

};