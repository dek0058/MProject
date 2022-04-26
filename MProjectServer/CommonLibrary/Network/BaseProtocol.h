#pragma once
#include "NetworkDefine.h"
#include "Utility/SHA256.h"

#define GENERATE_PROTOCOL_IMPLEMENT(class_name) \
public: \
	static std::vector<byte> const& GetHashCode() { \
		static std::vector<byte> hash_code = MSHA256::GenerateHashcode(##class_name); \
		return hash_code; \
	}

struct FPacket {
	uint tag;
	uint length;
	byte hash_code[PACKET_HASH_CODE_SIZE];
	std::vector<byte> data;

	FPacket() : tag(0), length(0) {
		std::memset(hash_code, 0, PACKET_HASH_CODE_SIZE);
		data.resize(PACKET_MAX_SIZE);
	}
};

class BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(BaseProtocol)
};


// test
#include "Packet/NTestPacket_generated.h"
class TestProtocol : public BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(TestProtocol)

public:

	static void CreatePacket() {

	}
};