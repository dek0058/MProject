#pragma once
#include "NetworkDefine.h"
#include "Utility/SHA256.h"
#include "Packet/Core_generated.h"
#include "Packet/Test_generated.h"

//#define GENERATE_PROTOCOL_CREATOR(class_name, ...) class_name() : __VA_ARGS__ {\
//		auto temp = MSHA256::GenerateHashcode(#class_name); \
//		std::copy(temp.begin(), temp.end(), hash_code); \
//	}

//struct FBaseProtocol {
//	byte hash_code[PACKET_HASH_CODE_SIZE];
//	uint lenth;
//	uint tag;
//	
//	GENERATE_PROTOCOL_CREATOR(FBaseProtocol, lenth(0), tag(0))
//};

using namespace MProject::Core;
using namespace MProject::Test;

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

struct FBaseProtocol {
	std::vector<byte> hash_code;
	FBaseProtocol() : hash_code(MSHA256::GenerateHashcode("FBaseProtocol")) {
		//flatbuffers::FlatBufferBuilder builder(PACKET_BUFFER_BUILDER_SIZE);
		//BasePacketBuilder packet_builder(builder);
		//auto p = packet_builder.Finish();
		//auto packet = flatbuffers::GetRoot<BasePacket>(builder.GetBufferPointer());
		//BasePacketBuilder builder()
		//auto h = CreateHeader(MSHA256::GenerateHashcode("FBaseProtocol"), 0, 0);
		//std::vector<byte> temp = MSHA256::GenerateHashcode("FBaseProtocol");
		//std::copy(temp.begin(), temp.end(), const_cast<uint8_t*>(packet.hash_code()->Data()));
		//packet.hash_code()->Data()
		
		//std::memcpy(packet.hash_code()->data(), temp.begin(), temp.end();
		//memcpy()
		//packet.hash_code().
	}
};

//// Example
//struct FMovementProtocol : public FBaseProtocol {
//	float x, y, z;
//	GENERATE_PROTOCOL_CREATOR(FMovementProtocol, x(0.0F), y(0.0F), z(0.0F))
//};
//
//struct FAttackProtocol : public FBaseProtocol {
//	float dmg;
//	GENERATE_PROTOCOL_CREATOR(FAttackProtocol, dmg(0.0F))
//};
