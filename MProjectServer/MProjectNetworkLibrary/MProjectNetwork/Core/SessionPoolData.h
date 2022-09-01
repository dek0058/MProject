#pragma once
#include "MProjectNetwork/NetworkDefine.h"


namespace mproject {
namespace network {

class Session;

struct FSessionPoolData {
public:
	FSessionPoolData() {}
	FSessionPoolData(std::shared_ptr<Session> _session) : session(_session) {}
public:
	bool occupied = false;
	std::shared_ptr<Session> session = nullptr;
};
}	// network
}	// mproject
