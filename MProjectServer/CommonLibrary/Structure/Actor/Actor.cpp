#include "Actor.h"
#include "Structure/Player/GPC.h"

Actor::Actor(uint _actor_key, std::weak_ptr<GPC> _game_player)
	: actor_key(_actor_key), game_player(_game_player) {
}

std::shared_ptr<Actor> Actor::Create(std::weak_ptr<GPC> _game_player, FVector _position, FQuaternion _rotation, FVector _scale) {
	if (true == _game_player.expired()) {
		LogManager::GetMutableInstance().GenericLog(ELogLevel::Warning, "Actor", "Create", "GPC is expired.");
		return std::shared_ptr<Actor>();
	}
	static uint key = 0;
	std::shared_ptr<Actor> actor = std::make_shared<Actor>(++key, _game_player);
	actor->SetTransform(_position, _rotation, _scale);
	actor->game_player.lock()->TakeActor(actor);
	return actor;
}

void Actor::LostOwner() {
	if (false == game_player.expired()) {
		game_player.lock()->LostActor(GetActorKey());
		game_player.reset();
	}
}

uint Actor::GetUserKey() const {
	if (true == game_player.expired()) {
		return 0;
	}
	else {
		return game_player.lock()->GetUserKey();
	}
}
