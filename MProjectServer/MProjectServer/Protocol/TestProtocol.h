#pragma once
#include "Network/BaseProtocol.h"
#include "Network/ProtocolHandler.h"
#include "Packet/NTestPacket_generated.h"

class TestProtocol : public BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(TestProtocol)

public:
	static std::unique_ptr<FPacket> CreatePacket(int _x, int _y, int _z) {
		START_PACKET(TestProtocol, 1, MProject::Packet::NTestPacketBuilder);

		packet_builder.add_x(_x);
		packet_builder.add_y(_y);
		packet_builder.add_z(_z);

		END_PACKET();
	}
};

class TestProtocolHandler final : public TProtocolHandler<TestProtocol> {
	virtual void OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet);
};
