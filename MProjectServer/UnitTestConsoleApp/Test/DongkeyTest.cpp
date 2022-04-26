#include "DongkeyTest.h"
#include "UnitTestSuite.h"
#include "UnitTestCaller.h"

#include <iostream>
#include <string>
#include <map>
#include <functional>

#include "MemoryPoolTest.h"

DongkeyTest::DongkeyTest(std::string const& _name) : UnitTestCase(_name) {
}

DongkeyTest::~DongkeyTest() {
}

void DongkeyTest::MapTest() {
	
	std::map<int, int> test_map{
		{0, 0}, {1, 0}, {2, 0}, {4, 0}, {5, 0} // not 3
	};

	std::cout << "\n삭제 테스트" << std::endl;
	try {
		
		auto iter = test_map.erase(3);
		std::cout << iter << std::endl;

		auto iter2 = test_map.erase(2);
		std::cout << iter2 << std::endl;

		auto iter3 = test_map.erase(4);
		std::cout << iter3 << std::endl;
		
	} catch(std::exception _exception) {
		std::cout << _exception.what() << std::endl;
	}
}

#include "Packet/Test_generated.h"
#include "flatbuffers/vector.h"
void DongkeyTest::FlatbuffersTest() {
	using Vector3 = MProject::Core::Vector3;
	using Transform = MProject::Core::Transform;
	/*
	auto print_test_object = [](MProject::Test::TestObject const* _test_object) {
		if (nullptr == _test_object) {
			std::cout << "nullptr" << std::endl;
			return;
		}
		std::cout << std::format("id:{}\nTransform(({}, {}, {}), ({}, {}, {}), ({}, {}, {}))",
			_test_object->id(),
			_test_object->transform()->position().x(), _test_object->transform()->position().y(), _test_object->transform()->position().z(),
			_test_object->transform()->rotation().x(), _test_object->transform()->rotation().y(), _test_object->transform()->rotation().z(),
			_test_object->transform()->scale().x(), _test_object->transform()->scale().y(), _test_object->transform()->scale().z());
	};

	int id = 1;
	Vector3 position(101, 50, 22);
	Vector3 rotation(0, 180, 0);
	Vector3 scale(1, 1, 1);
	Transform* transform = new Transform(position, rotation, scale);

	flatbuffers::FlatBufferBuilder builder(1024); // default size 1024.
	MProject::Test::TestObjectBuilder test_object_builder(builder);
	test_object_builder.add_id(id);
	test_object_builder.add_transform(transform);
	auto test_object = test_object_builder.Finish();

	// or
	//auto test_object = MProject::Test::CreateTestObject(builder, id, transform);
	builder.Finish(test_object);
	
	auto buf = builder.GetBufferPointer();
	int size = builder.GetSize();

	std::cout << "buf : " << buf << std::endl;
	std::cout << "size : " << size << std::endl;

	auto test_object_buf = flatbuffers::GetRoot<MProject::Test::TestObject>(buf);
	print_test_object(test_object_buf);
	*/
}

#include "Utility/SHA256.h"
#include "Network/BaseProtocol.h"


void DongkeyTest::GenerateHashCodeTest() {

	auto temp = MSHA256::GenerateHashcode("FBaseProtocol");
	//FBaseProtocol protocol;

	int cnt = 0;
	for(auto i = temp.begin(); i != temp.end(); ++i) {
		std::cout << std::hex << (unsigned int)(*i) << " ";
		++cnt;
	}
	std::cout << std::endl;
	std::cout << cnt << std::endl;

	flatbuffers::FlatBufferBuilder builder(PACKET_BUFFER_BUILDER_SIZE);
	BasePacketBuilder packet_builder(builder);
	Header* header = new Header();
	packet_builder.add_header(header);
	auto p = packet_builder.Finish();
	builder.Finish(p);
	BasePacket const* packet = flatbuffers::GetRoot<BasePacket>(builder.GetBufferPointer());

	std::cout << builder.GetSize() << std::endl;
	

	//builder.CreateStruct
	
	//using MovementPacket = MProject::Movement::MovementPacket;
	//using Packet = MProject::Core::Packet;
	//
	//flatbuffers::FlatBufferBuilder builder(1024); // default size 1024.
	//byte hash_code[20];
	//auto temp = MSHA256::GenerateHashcode("MovementPacket");
	//std::copy(temp.begin(), temp.end(), hash_code);
	//Packet* packet = new Packet(hash_code, 0, 0);
	//auto movement_packet = MProject::Movement::CreateMovementPacket(builder, packet);
	//
	//std::cout << std::endl;
	//for (auto h : hash_code) {
	//	std::cout << std::hex << (unsigned int)h;
	//} // length = 20
	//std::cout << std::format("\nsize:{}\n", sizeof(MProject::Movement::MovementPacket)) << std::endl;
	//std::cout << std::endl;

	//FAttackProtocol atk_packet;
	//for (auto h : atk_packet.hash_code) {
	//	std::cout << std::hex << (unsigned int)h;
	//} // length = 20
	//std::cout << std::format("\nsize:{}\n", sizeof(FAttackProtocol)) << std::endl;
	//std::cout << std::endl;
}

#include "Utility/CircularBuffer.h"

void DongkeyTest::PacketTest() {
	
	CircularBuffer_M circular_buffer(1024);
	std::vector<byte> buffer;
	buffer.reserve(1024);
	
	FBaseProtocol base_protocol;
	
	std::cout << "\nbase protocol\n";
	for (int i = 0; i < base_protocol.hash_code.size(); ++i) {
		std::cout << std::hex << (unsigned int)base_protocol.hash_code[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "\nbuffer\n";
	
	buffer.resize(base_protocol.hash_code.size());
	std::copy(base_protocol.hash_code.begin(), base_protocol.hash_code.end(), buffer.data());
	for (int i = 0; i < base_protocol.hash_code.size(); ++i) {
		std::cout << std::hex << (unsigned int)buffer[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "\nCreate Packet\n";
	FPacket* packet = new FPacket;
	packet->tag = 1;

	packet->length += static_cast<uint>(buffer.size() * sizeof(byte));
	std::copy(base_protocol.hash_code.begin(), base_protocol.hash_code.end(), packet->hash_code);
	
	//packet->data.resize(100);

	size_t cur_size = 0;
	std::memcpy(packet->data.data() + cur_size, &packet->tag, PACKET_TAG_SIZE);
	cur_size += PACKET_TAG_SIZE;
	//byte tag_buffer[int_size] = {0};
	//std::memcpy(&tag_buffer, &packet->tag, sizeof(uint));
	
	std::memcpy(packet->data.data() + cur_size, &packet->length, PACKET_LEGNTH_SIZE);
	cur_size += PACKET_LEGNTH_SIZE;
	//byte length_buffer[int_size] = {0};
	//std::memcpy(&length_buffer, &packet->length, sizeof(uint));
	
	//packet->data.insert(0, packet->hash_code);
	std::memcpy(packet->data.data() + cur_size, &packet->hash_code, PACKET_HASH_CODE_SIZE);
	cur_size += PACKET_HASH_CODE_SIZE;
		
	std::cout << std::format("size[{}] tag[{}] length[{}]\n", cur_size, packet->tag, packet->length);
	for (int i = 0; i < base_protocol.hash_code.size(); ++i) {
		std::cout << std::hex << (unsigned int)packet->hash_code[i] << " ";
	}
	std::cout << std::endl;

	circular_buffer.Put(packet->data.data(), cur_size);

	//packet->data.emplace_back(packet->hash_code);

	

	std::cout << "\nSend Packet\n";
	std::vector<byte> recv_buffer(1024);

	circular_buffer.Get(recv_buffer.data(), PACKET_HEADER_SIZE);
	
	uint tag = 0;
	uint length = 0;
	byte hash_code[PACKET_HASH_CODE_SIZE] = { 0 };

	std::memcpy(&tag, recv_buffer.data(), PACKET_TAG_SIZE);
	std::memcpy(&length, recv_buffer.data() + PACKET_TAG_SIZE, PACKET_LEGNTH_SIZE);
	std::memcpy(&hash_code, recv_buffer.data() + PACKET_TAG_SIZE + PACKET_LEGNTH_SIZE, PACKET_HASH_CODE_SIZE);
	
	std::cout << std::format("tag[{}] length[{}]\n", tag, length);
	for (int i = 0; i < base_protocol.hash_code.size(); ++i) {
		std::cout << std::hex << (unsigned int)hash_code[i] << " ";
	}
	std::cout << std::endl;

	delete packet;
}

UnitTest* DongkeyTest::Suite() {
	UnitTestSuite* suite = new UnitTestSuite("DongkeyTest");
	//TUnitTest_AddTest(suite, DongkeyTest, MapTest);
	//TUnitTest_AddTest(suite, DongkeyTest, FlatbuffersTest);
	//TUnitTest_AddTest(suite, DongkeyTest, GenerateHashCodeTest);
	TUnitTest_AddTest(suite, DongkeyTest, PacketTest);
	return suite;
}

