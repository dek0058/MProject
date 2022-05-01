#pragma once
#include "NetworkDefine.h"
#include "Utility/MSHA256.h"
#include "Utility/UniversalToolkit.h"
#include "flatbuffers/buffer.h"

#pragma region GENERATE_PROTOCOL_IMPLEMENT
#define GENERATE_PROTOCOL_IMPLEMENT(class_name) \
public: \
	static std::string const& ToString() { \
		static std::string str = #class_name; \
		return str; \
	} \
	static std::vector<byte> const& GetHashCode() { \
		static std::vector<byte> hash_code = MSHA256::GenerateHashcode(class_name::ToString()); \
		return hash_code; \
	} \
	static std::string const& GetHashCodeString() { \
		static std::string hash_code_string = UniversalToolkit::Digest2Hex(class_name::GetHashCode()); \
		return hash_code_string; \
	}
#pragma endregion

#pragma region CREATE_PACKET
#define START_PACKET(class_name, packet_tag, builder_class) \
	std::unique_ptr<FPacket> packet = std::make_unique<FPacket>(); \
	packet->tag = packet_tag; \
	std::copy(class_name::GetHashCode().begin(), class_name::GetHashCode().end(), packet->hash_code.data()); \
	flatbuffers::FlatBufferBuilder builder(PACKET_MAX_SIZE); \
	builder_class packet_builder(builder)

#define END_PACKET() \
	auto packet_data = packet_builder.Finish(); \
	builder.Finish(packet_data); \
	packet->data = std::vector<byte>(builder.GetBufferPointer(), builder.GetBufferPointer() + builder.GetSize()); \
	packet->length = static_cast<uint>(packet->data.size()); \
	return std::move(packet)
#pragma endregion


struct FPacket {
	uint tag;
	uint length;
	std::vector<byte> hash_code;
	std::vector<byte> data;

	FPacket() : tag(0), length(0), hash_code(PACKET_HASH_CODE_SIZE) { ; }
};

class BaseProtocol {
	GENERATE_PROTOCOL_IMPLEMENT(BaseProtocol)

public:
	template<typename T>
	static T const* GetData(byte* _data) {
		return flatbuffers::template GetRoot<T>(_data);
	}

	template<typename T>
	void ReceivePacket(FPacket* _packet) { 
		auto packet = BaseProtocol::GetData<T>(_packet->data.data());
	}
};

