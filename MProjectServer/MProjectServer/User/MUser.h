#pragma once
#include "Network/NetworkDefine.h"

#include "Structure/Player/GPC.h" // include ActorStructure.h

struct FSession;
struct FPacket;
class MWorld;

namespace MProject {
	namespace Packet {
		enum Tag : uint32_t;
	}
}

class MUser {
public:

	MUser(std::shared_ptr<FSession> _session, uint _key);

	void SendPacket(std::unique_ptr<FPacket> _packet);
	void SendTag();
	

	//! Setter
	void SetTags(std::vector<uint> _tags) {
		tags = _tags;
	}

	void SetWorld(std::shared_ptr<MWorld> _world) {
		world = std::weak_ptr<MWorld>(_world);
	}

	void LeftWorld() {
		tags.clear();
		world.reset();
	}

	//! Getter
	uint SessionKey() const;
	uint GetUserKey() const {
		return key;
	}
	std::vector<uint> GetPacketTagList() const {
		return tags;
	}
	
	std::weak_ptr<MWorld> GetWorld() {
		return world;
	}

private:

	uint key;
	std::shared_ptr<FSession> session;
	std::shared_ptr<GPC> game_player_controller;

	std::vector<uint> tags;

	std::weak_ptr<MWorld> world;

};

