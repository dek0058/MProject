#pragma once
#include "NetworkDefine.h"
#include "Utility/SHA256.h"

#define GENERATE_PROTOCOL_CREATOR(class_name, ...) class_name() : __VA_ARGS__ {\
		auto temp = MSHA256::GenerateHashcode(#class_name); \
		std::copy(temp.begin(), temp.end(), hash_code); \
	}

struct FBaseProtocol {
	byte hash_code[PACKET_HASH_CODE_SIZE];
	uint lenth;
	uint tag;
	
	GENERATE_PROTOCOL_CREATOR(FBaseProtocol, lenth(0), tag(0))
};

/* Example
struct FMovementProtocol : public FBaseProtocol {
	float x, y, z;
	GENERATE_PROTOCOL_CREATOR(FMovementProtocol, x(0.0F), y(0.0F), z(0.0F))
};

struct FAttackProtocol : public FBaseProtocol {
	float dmg;
	GENERATE_PROTOCOL_CREATOR(FAttackProtocol, dmg(0.0F))
};
*/