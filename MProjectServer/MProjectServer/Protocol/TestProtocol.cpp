#include "TestProtocol.h"

#include "Core/MLogger.h"


void TestProtocolHandler::OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) {
	MLogger::GetMutableInstance().LogError("TestProtocolHandler::OnReceivePacket");
	MLogger::GetMutableInstance().LogError(std::format("SessionKey:{}", _session_key));
	auto recv_test_protocol = BaseProtocol::GetData<MProject::Packet::NTestPacket>(_packet->data.data());
	MLogger::GetMutableInstance().LogError(std::format("Packet: x:{}, y:{}, z:{}", recv_test_protocol->x(), recv_test_protocol->y(), recv_test_protocol->z()));
}
