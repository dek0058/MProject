#include "MWorld.h"


MWorld::MWorld(uint _key, EWorldType _world_type) :
	key(_key), world_type(_world_type) {
	
}


void MWorld::JoinUser(std::shared_ptr<MUser> _user) {

}

void MWorld::LeftUser(std::shared_ptr<MUser> _user) {

}

void MWorld::JoinActor(std::shared_ptr<Actor> _actor) {

}

void MWorld::LeftActor(std::shared_ptr<Actor> _actor) {

}
