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
	std::vector<byte> buffer;
	buffer.reserve(1024);
	

	std::cout << "\nbase protocol\n";
	for (int i = 0; i < BaseProtocol::GetHashCode().size(); ++i) {
		std::cout << std::hex << (unsigned int)BaseProtocol::GetHashCode()[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "\nbuffer\n";
	
	buffer.resize(BaseProtocol::GetHashCode().size());
	std::copy(BaseProtocol::GetHashCode().begin(), BaseProtocol::GetHashCode().end(), buffer.data());
	for (int i = 0; i < BaseProtocol::GetHashCode().size(); ++i) {
		std::cout << std::hex << (unsigned int)buffer[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "\nCreate Packet\n";
	FPacket* packet = new FPacket;
	packet->tag = 1;

	packet->length += static_cast<uint>(buffer.size() * sizeof(byte));
	std::copy(buffer.begin(), buffer.end(), packet->hash_code);
	
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
	for (auto& item : packet->hash_code) {
		std::cout << std::hex << (unsigned int)item << " ";
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
	for (auto& item : hash_code) {
		std::cout << std::hex << (unsigned int)item << " ";
	}
	std::cout << std::endl;

	delete packet;
}

UnitTest* DongkeyTest::Suite() {
	UnitTestSuite* suite = new UnitTestSuite("DongkeyTest");
	//TUnitTest_AddTest(suite, DongkeyTest, MapTest);
	TUnitTest_AddTest(suite, DongkeyTest, PacketTest);
	return suite;
}

