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


#include "Utility/SHA256.h"
#include "Network/BaseProtocol.h"
#include "Utility/CircularBuffer.h"

void DongkeyTest::PacketTest() {
	
	CircularBuffer_M circular_buffer(1024);
	std::cout << std::endl;
	std::cout << "Send Packet\n";
	std::unique_ptr<FPacket> packet = TestProtocol::CreatePacket(1, 2, 3);

	std::vector<byte> buffer(PACKET_HEADER_SIZE + packet->data.size());
	std::memcpy(buffer.data(), &packet->tag, PACKET_TAG_SIZE);
	std::memcpy(buffer.data() + PACKET_TAG_SIZE, &packet->length, PACKET_LEGNTH_SIZE);
	std::memcpy(buffer.data() + PACKET_TAG_SIZE + PACKET_LEGNTH_SIZE, &packet->hash_code, PACKET_HASH_CODE_SIZE);
	std::memcpy(buffer.data() + PACKET_TAG_SIZE + PACKET_LEGNTH_SIZE + PACKET_HASH_CODE_SIZE, packet->data.data(), packet->length);
	circular_buffer.Put(buffer.data(), buffer.size());
	std::cout << std::format("Circular buffer size:{}\n", circular_buffer.UsedSize());

	std::cout << std::format("tag[{}] length[{}]\n", packet->tag, packet->length);
	for (auto& item : packet->hash_code) {
		std::cout << std::hex << (unsigned int)item << " ";
	}
	auto send_test_protocol = BaseProtocol::GetData<MProject::Packet::NTestPacket>(packet->data.data());
	std::cout << std::endl;
	std::cout << std::format("x:{}, y:{}, z:{}", send_test_protocol->x(), send_test_protocol->y(), send_test_protocol->z()) << std::endl;

	std::cout << std::endl;
	std::cout << "Receive Packet\n";
	std::vector<byte> recv_buffer(PACKET_HEADER_SIZE);
	circular_buffer.Get(recv_buffer.data(), PACKET_HEADER_SIZE);
	std::cout << std::format("Circular buffer size:{}\n", circular_buffer.UsedSize());

	uint tag = 0;
	uint length = 0;
	byte hash_code[PACKET_HASH_CODE_SIZE] = { 0 };

	std::memcpy(&tag, recv_buffer.data(), PACKET_TAG_SIZE);
	std::memcpy(&length, recv_buffer.data() + PACKET_TAG_SIZE, PACKET_LEGNTH_SIZE);
	std::memcpy(&hash_code, recv_buffer.data() + PACKET_TAG_SIZE + PACKET_LEGNTH_SIZE, PACKET_HASH_CODE_SIZE);

	std::vector<byte> packet_data(length);
	circular_buffer.Get(packet_data.data(), length);
	std::cout << std::format("Circular buffer size:{}\n", circular_buffer.UsedSize());
	//std::memcpy(packet_data.data(), recv_buffer.data() + PACKET_TAG_SIZE + PACKET_LEGNTH_SIZE + PACKET_HASH_CODE_SIZE, length);
	auto recv_test_protocol = BaseProtocol::GetData<MProject::Packet::NTestPacket>(packet_data.data());

	std::cout << std::format("tag[{}] length[{}]\n", tag, length);
	for (auto& item : hash_code) {
		std::cout << std::hex << (unsigned int)item << " ";
	}
	std::cout << std::endl;
	std::cout << std::format("x:{}, y:{}, z:{}", recv_test_protocol->x(), recv_test_protocol->y(), recv_test_protocol->z()) << std::endl;
	std::cout << std::endl;
}

UnitTest* DongkeyTest::Suite() {
	UnitTestSuite* suite = new UnitTestSuite("DongkeyTest");
	//TUnitTest_AddTest(suite, DongkeyTest, MapTest);
	TUnitTest_AddTest(suite, DongkeyTest, PacketTest);
	return suite;
}

