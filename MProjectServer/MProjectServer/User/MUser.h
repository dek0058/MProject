#pragma once
#include "Network/NetworkDefine.h"

struct FSession;
struct FPacket;
class MWorld;
class GPC;
class ILogger;

namespace MProject {
	namespace Packet {
		enum Tag : uint32_t;
	}
}

class MUser : public std::enable_shared_from_this<MUser> {
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

	void LeftWorld();

	//! Getter
	uint SessionKey() const;
	uint GetUserKey() const {
		return key;
	}
	std::vector<uint> GetPacketTagList() const {
		return tags;
	}
	
	std::weak_ptr<GPC> GetGamePlayer() {
		return std::weak_ptr<GPC>(game_player_controller);
	}

	std::weak_ptr<MWorld> GetWorld() {
		return world;
	}



private:

	//! Getter

	std::weak_ptr<ILogger> logger;
	std::weak_ptr<ILogger> GetLogger();

private:

	uint key;
	std::shared_ptr<FSession> session;
	std::shared_ptr<GPC> game_player_controller;

	std::vector<uint> tags;

	std::weak_ptr<MWorld> world;

};

