#pragma once
#include "Network/NetworkDefine.h"

#include "Structure/Player/GPC.h" // include ActorStructure.h

struct FSession;

class MUser {
public:

	MUser(std::shared_ptr<FSession> _session, uint _key);


	uint SessionKey() const;
	uint GetUserKey() const;
	

private:

	uint key;
	std::shared_ptr<FSession> session;

	
	std::shared_ptr<GPC> game_player_controller;
		
};

