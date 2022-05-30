#pragma once
#include "GlobalDefine.h"
#include "Core/LogManager.h"
#include "Structure/Core/Transform.h"
#include "Structure/Player/GPC.h"
#include "Packet/Actor_generated.h"

class Actor : public std::enable_shared_from_this<Actor> {
public:

	Actor(uint _actor_key, std::weak_ptr<GPC> _game_player)
		: actor_key(_actor_key), game_player(_game_player) {
		_game_player.lock()->TakeActor(shared_from_this());
	}


	static std::shared_ptr<Actor> Create(std::weak_ptr<GPC> _game_player, FVector _position, FQuaternion _rotation, FVector _scale) {
		if (true == _game_player.expired()) {
			LogManager::GetMutableInstance().GenericLog(ELogLevel::Warning, "Actor", "Create", "GPC is expired.");
			return std::shared_ptr<Actor>();
		}
		static uint key = 0;
		std::shared_ptr<Actor> actor(new Actor(++key, _game_player));
		actor->SetTransform(_position, _rotation, _scale);
		return actor;
	}


	//! Setter

	void SetTransform(FVector _position, FQuaternion _rotation, FVector _scale) {
		transform.position = _position;
		transform.rotation = _rotation;
		transform.scale = _scale;
	}

	void LostOwner() {
		if (false == game_player.expired()) {
			game_player.lock()->LostActor(GetActorKey());
			game_player.reset();
		}
	}

	void SetOwner(std::weak_ptr<GPC> _game_player) {
		LostOwner();
		_game_player = game_player;
	}

	//! Getter

	flatbuffers::Offset<Packet::Actor> ToFaltbuffer(flatbuffers::FlatBufferBuilder& _builder) {
		return Packet::CreateActor(_builder, GetActorKey(), GetUserKey(), transform.ToFaltbuffer(_builder));
	}

	uint GetActorKey() const {
		return actor_key;
	}

	uint GetUserKey() const {
		if (true == game_player.expired()) {
			return 0;
		} else {
			return game_player.lock()->GetUserKey();
		}
	}

	FVector& GetPosition() {
		return transform.position;
	}

	FQuaternion& GetRotation() {
		return transform.rotation;
	}

	FVector& GetScale() {
		return transform.scale;
	}
	
private:
	uint actor_key;
	std::weak_ptr<GPC> game_player;
	FTransform transform;

};
