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

std::vector<std::weak_ptr<Actor>> GPC::GetActors() {
	std::vector<std::weak_ptr<Actor>> result;
	for (auto& [key, actor] : actor_map) {
		if (nullptr == actor.get()) {
			// TODO 삭제 필요
			continue;
		}
		result.emplace_back(std::weak_ptr<Actor>(actor));
	}
	return result;
}