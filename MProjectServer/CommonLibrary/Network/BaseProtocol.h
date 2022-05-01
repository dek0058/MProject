#pragma once
#include "NetworkDefine.h"
#include "Utility/MSHA256.h"
#include "Utility/UniversalToolkit.h"
#include "flatbuffers/buffer.h"
#include "Packet/PacketTag_generated.h"

#pragma region GENERATE_PROTOCOL_IMPLEMENT
#define GENERATE_PROTOCOL_IMPLEMENT(class_name, packet_tag) \
public: \
	virtual std::string const& ToString() override { \
		static std::string str = #class_name; \
		return str; \
	} \
	virtual std::vector<byte> const& GetHashCode() override { \
		static std::vector<byte> hash_code = MSHA256::GenerateHashcode(ToString()); \
		return hash_code; \
	} \
	virtual std::string const& GetHashCodeString() override { \
		static std::string hash_code_string = UniversalToolkit::Digest2Hex(GetHashCode()); \
		return hash_code_string; \
	} \
	virtual uint GetPacketTag() override { \
		static MProject::Packet::Tag tag = packet_tag; \
		return static_cast<uint>(tag); \
	}
#pragma endregion

#pragma region CREATE_PACKET
#define START_PACKET(class_name, builder_class) \
	class_name my_class; \
	std::unique_ptr<FPacket> packet = std::make_unique<FPacket>(); \
	packet->tag = my_class.GetPacketTag(); \
	std::copy(my_class.GetHashCode().begin(), my_class.GetHashCode().end(), packet->hash_code.data()); \
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
public:
	template<typename T>
	static T const* GetData(byte* _data) {
		return flatbuffers::template GetRoot<T>(_data);
	}

	template<typename T>
	void ReceivePacket(FPacket* _packet) { 
		auto packet = BaseProtocol::GetData<T>(_packet->data.data());
	}

public:
	virtual std::string const& ToString() = 0;
	virtual std::vector<byte> const& GetHashCode() = 0;
	virtual std::string const& GetHashCodeString() = 0;
	virtual uint GetPacketTag() = 0;
};

class ProtocolMessage : public BaseProtocol {
public:
	GENERATE_PROTOCOL_IMPLEMENT(ProtocolMessage, MProject::Packet::Tag::Tag_Create)

	static std::unique_ptr<FPacket> CreatePacket(std::vector<std::tuple<uint, std::vector<byte>>> _protocol_array) {
		START_PACKET(ProtocolMessage, MProject::Packet::NProtocolMessageBuilder);

		std::vector<MProject::Packet::FProtocol> protocol_array;
		protocol_array.reserve(_protocol_array.size());
		for (auto [tag, hash_code] : _protocol_array) {
			protocol_array.emplace_back(
				MProject::Packet::FProtocol(
					tag, 
					flatbuffers::span<const byte, PACKET_HASH_CODE_SIZE>(hash_code.begin(), hash_code.begin() + PACKET_HASH_CODE_SIZE)
				)
			);
		}

		auto ttt = builder.CreateVectorOfStructs(protocol_array.data(), protocol_array.size());

		//packet_builder.add_protocol();
		END_PACKET();
	}
	
public:
	
};
