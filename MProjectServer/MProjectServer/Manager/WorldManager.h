#pragma once
#include "Network/NetworkDefine.h"
#include "Utility/TSingleton.h"
#include "Structure/WorldStructure.h"
#include "World/MWorld.h"

struct FSession;
class MUser;
class ILogger;

class WorldManager : public TSingleton<WorldManager> {
	
	using WorldMap = std::map<uint/*Key*/, std::shared_ptr<MWorld>>;

	static uint GetWorldKey() {
		// TODO 테이블 데이터로 대체 해야함...
		static uint key = 0;
		return ++key;
	}
	
protected:
	WorldManager();

public:

	void JoinUserToWorld(std::weak_ptr<MUser> _user, uint _world_key);


	//! Getter

	std::weak_ptr<MWorld> FindWorld(uint _world_key) {
		if (true == world_map.contains(_world_key)) {
			return std::weak_ptr<MWorld>(world_map[_world_key]);
		} else {
			return std::weak_ptr<MWorld>();
		}
	}

	template<typename T = MWorld>
	std::weak_ptr<T> FindWorld() {
		for (auto iter : world_map) {
			auto world = iter.second;
			if (nullptr != world.get()) {
				if (auto cast = std::dynamic_pointer_cast<T>(world)) {
					return std::weak_ptr<T>(cast);
				}
			}
		}
		return std::weak_ptr<T>();
	}
	



private:

	
	//! Getter

	std::weak_ptr<ILogger> logger;
	std::weak_ptr<ILogger> GetLogger();

	//! Utility

	template<typename T = MWorld>
	void Add();

public:

	
private:
	
	WorldMap world_map;
	

};
