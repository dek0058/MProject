#include "GPC.h"
#include "Structure/Actor/Actor.h"

void GPC::TakeActor(std::shared_ptr<Actor> _actor) {
	if (nullptr == _actor.get()) {
		LogManager::GetMutableInstance().GenericLog(ELogLevel::Warning, "GPC", "TakeActor", "Actor is null.");
		return;
	}
	if (false == actor_map.contains(_actor->GetActorKey())) {
		actor_map.emplace(_actor->GetActorKey(), _actor);
	}
	_actor->SetOwner(std::weak_ptr<GPC>(shared_from_this()));
}

void GPC::LostActor(uint _actor_key) {
	if (true == actor_map.contains(_actor_key)) {
			actor_map.erase(_actor_key);
	}
}
