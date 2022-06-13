#pragma once

#include "GuardDefine.h"
#include "Network/NetworkDefine.h"

struct FPacket;

class NetworkToolkit {
	DELETE_REFERENCE_CREATOR(NetworkToolkit)

public:

	static std::vector<byte> GetPacketData(std::unique_ptr<FPacket> _packet);
	static std::vector<byte> GetPacketData(std::shared_ptr<FPacket> _packet);

};
