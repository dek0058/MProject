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
}

#include "Utility/SHA256.h"
#include "Network/BaseProtocol.h"
#include "Packet/Movement_generated.h"


void DongkeyTest::GenerateHashCodeTest() {
	using MovementPacket = MProject::Movement::MovementPacket;
	using Packet = MProject::Core::Packet;
	
	flatbuffers::FlatBufferBuilder builder(1024); // default size 1024.
	byte hash_code[20];
	auto temp = MSHA256::GenerateHashcode("MovementPacket");
	std::copy(temp.begin(), temp.end(), hash_code);
	Packet* packet = new Packet(hash_code, 0, 0);
	auto movement_packet = MProject::Movement::CreateMovementPacket(builder, packet);
	
	std::cout << std::endl;
	for (auto h : hash_code) {
		std::cout << std::hex << (unsigned int)h;
	} // length = 20
	std::cout << std::format("\nsize:{}\n", sizeof(MProject::Movement::MovementPacket)) << std::endl;
	std::cout << std::endl;

	//FAttackProtocol atk_packet;
	//for (auto h : atk_packet.hash_code) {
	//	std::cout << std::hex << (unsigned int)h;
	//} // length = 20
	//std::cout << std::format("\nsize:{}\n", sizeof(FAttackProtocol)) << std::endl;
	//std::cout << std::endl;
}

UnitTest* DongkeyTest::Suite() {
	UnitTestSuite* suite = new UnitTestSuite("DongkeyTest");
	//TUnitTest_AddTest(suite, DongkeyTest, MapTest);
	//TUnitTest_AddTest(suite, DongkeyTest, FlatbuffersTest);
	TUnitTest_AddTest(suite, DongkeyTest, GenerateHashCodeTest);
	return suite;
}

