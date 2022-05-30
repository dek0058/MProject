#include "Actor.h"
#include "Structure/Player/GPC.h"

Actor::Actor(uint _actor_key, std::weak_ptr<GPC> _game_player)
	: actor_key(_actor_key) {
	game_player = _game_player;
	game_player.lock()->TakeActor(shared_from_this());
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
