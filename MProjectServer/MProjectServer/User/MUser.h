#pragma once
#include "Network/NetworkDefine.h"

#include "Structure/Player/GPC.h" // include ActorStructure.h

struct FSession;
struct FPacket;
class HeadServer;

namespace MProject {
	namespace Packet {
		enum Tag : uint32_t;
	}
}

class MUser {
public:

	MUser(std::shared_ptr<FSession> _session, uint _key);


	void SetTags(std::vector<uint> _tags) {
		tags = _tags;
	}

	void SendPacket(std::unique_ptr<FPacket> _packet);
	
	//! Getter
	uint SessionKey() const;
	uint GetUserKey() const {
		return key;
	}
	std::vector<uint> GetPacketTagList() const {
		return tags;
	}
	

private:

	uint key;
	std::shared_ptr<FSession> session;
	std::shared_ptr<GPC> game_player_controller;

	std::vector<uint> tags;
};

