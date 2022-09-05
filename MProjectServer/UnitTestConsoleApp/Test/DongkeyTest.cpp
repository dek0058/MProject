#include "DongkeyTest.h"
#include "UnitTestSuite.h"
#include "UnitTestCaller.h"

#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <thread>

#include "Utility/MSHA256.h"
#include "Network/BaseProtocol.h"
#include "Utility/CircularBuffer.h"

DongkeyTest::DongkeyTest(std::string const& _name) : UnitTestCase(_name) {
}

DongkeyTest::~DongkeyTest() {
}

#include "Utility/MRandom.h"

void DongkeyTest::MapTest() {
	
	//X<splitmix64, "Pyrophoricity"> z;        // OK, string-literal is a constructor argument to A

	/*for (int i = 0; i < 100; ++i) {
		auto a = MRandom<splitmix64>::GetRandom<unsigned long long>() % 5;
		std::cout << a << std::endl;
	}

	for (int i = 0; i < 100; ++i) {
		auto a = MRandom<splitmix32>::GetRandom<unsigned long>() % 5;
		std::cout << a << std::endl;
	}*/

}

void DongkeyTest::MapBenchmark() {
	
	std::map<int, int> int_map;
	std::map<std::string, int> str_map;
	
	std::cout << "Create Data!" << std::endl;
	
	std::thread create_int_thread([&int_map]() {
		clock_t start = clock();
		for(uint i = 0;	i < 1'000'000; ++i) {
			int_map.emplace(i, i);
		}
		clock_t end = clock();
		double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
		std::cout << "Create Complete int_map:" << time << std::endl;
	});

	std::thread create_str_thread([&str_map]() {
		clock_t start = clock();
		for(uint i = 0;	i < 1'000'000; ++i) {
			str_map.emplace(UniversalToolkit::Digest2Hex(MSHA256::GenerateHashcode(std::to_string(i))), i);
		}
		clock_t end = clock();
		double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
		std::cout << "Create Complete str_map:" << time << std::endl;
	});
	
	create_int_thread.join();
	create_str_thread.join();

	std::vector<uint> int_keys;
	int_keys.reserve(1'000'000);
	
	std::vector<std::string> str_keys;
	str_keys.reserve(1'000'000);

	for(uint i = 0; i < 1'000'000; ++i) {
		auto rand = MRandom<splitmix32>::GetRandom<unsigned long>() % 1'000'000;
		int_keys.emplace_back(rand);
		str_keys.emplace_back(UniversalToolkit::Digest2Hex(MSHA256::GenerateHashcode(std::to_string(rand))));
	}

	std::cout << "Search Data!" << std::endl;
	std::thread search_int_thread([&int_map, int_keys]() {
		clock_t start = clock();
		for (int a = 0; a < 1'000'000; ++a)
		{
			for (uint i = 0; i < int_keys.size(); ++i) {
				auto r = int_map.find(int_keys[i]);
			}
		}
		
		clock_t end = clock();
		double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
		std::cout << "Search Complete int_map:" << time << std::endl;
	});

	std::thread search_str_thread([&str_map, str_keys]()
	{
		clock_t start = clock();
		for (int a = 0; a < 1'000'000; ++a)
		{
			for (uint i = 0; i < str_keys.size(); ++i) {
				auto r =str_map.find(str_keys[i]);
			}
		}
		clock_t end = clock();
		double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
		std::cout << "Search Complete str_map:" << time << std::endl;
	});

	search_int_thread.join();
	search_str_thread.join();

	std::cout << "Benchmark Complete!" << std::endl;
}



//#include "Protocol/TestProtocol.h"
void DongkeyTest::PacketTest() {
	//CircularBuffer_M circular_buffer(1024);
	//std::cout << std::endl;
	//std::cout << UniversalToolkit::Digest2Hex(MSHA256::GenerateHashcode("TestProtocol")) << std::endl;
	//
	//std::cout << "Send Packet\n";
	//std::unique_ptr<FPacket> packet = TestProtocol::CreatePacket(1, 2, 3);

	//std::vector<byte> buffer(PACKET_HEADER_SIZE + packet->data.size());
	//std::memcpy(buffer.data(), &packet->tag, PACKET_TAG_SIZE);
	//std::memcpy(buffer.data() + PACKET_TAG_SIZE, &packet->length, PACKET_LEGNTH_SIZE);
	//std::memcpy(buffer.data() + PACKET_TAG_SIZE + PACKET_LEGNTH_SIZE, packet->hash_code.data(), PACKET_HASH_CODE_SIZE);
	//std::memcpy(buffer.data() + PACKET_TAG_SIZE + PACKET_LEGNTH_SIZE + PACKET_HASH_CODE_SIZE, packet->data.data(), packet->length);
	//circular_buffer.Put(buffer.data(), buffer.size());
	//std::cout << std::format("Circular buffer size:{}\n", circular_buffer.UsedSize());

	//std::cout << std::format("tag[{}] length[{}]\n", packet->tag, packet->length);
	//std::cout << std::format("hashcode:{}, hashcode size:{}\n", packet->hash_code.size(), PACKET_HASH_CODE_SIZE);
	//for (auto& item : packet->hash_code) {
	//	std::cout << std::hex << (unsigned int)item << " ";
	//}
	//std::cout << std::endl;

	//auto send_test_protocol = BaseProtocol::GetData<MProject::Packet::NTestPacket>(packet->data.data());
	//std::cout << std::endl;
	//std::cout << std::format("x:{}, y:{}, z:{}", send_test_protocol->x(), send_test_protocol->y(), send_test_protocol->z()) << std::endl;

	//std::cout << std::endl;
	//std::cout << "Receive Packet\n";
	//std::vector<byte> recv_buffer(PACKET_HEADER_SIZE);
	//circular_buffer.Get(recv_buffer.data(), PACKET_HEADER_SIZE);
	//std::cout << std::format("Circular buffer size:{}\n", circular_buffer.UsedSize());

	//uint tag = 0;
	//uint length = 0;
	//byte hash_code[PACKET_HASH_CODE_SIZE] = { 0 };
	////std::vector<byte> hash_code(PACKET_HASH_CODE_SIZE);

	//std::memcpy(&tag, recv_buffer.data(), PACKET_TAG_SIZE);
	//std::memcpy(&length, recv_buffer.data() + PACKET_TAG_SIZE, PACKET_LEGNTH_SIZE);
	//std::memcpy(&hash_code, recv_buffer.data() + PACKET_TAG_SIZE + PACKET_LEGNTH_SIZE, PACKET_HASH_CODE_SIZE);

	//std::vector<byte> packet_data(length);
	//circular_buffer.Get(packet_data.data(), length);
	//std::cout << std::format("Circular buffer size:{}\n", circular_buffer.UsedSize());
	////std::memcpy(packet_data.data(), recv_buffer.data() + PACKET_TAG_SIZE + PACKET_LEGNTH_SIZE + PACKET_HASH_CODE_SIZE, length);
	//auto recv_test_protocol = BaseProtocol::GetData<MProject::Packet::NTestPacket>(packet_data.data());

	//std::cout << std::format("tag[{}] length[{}]\n", tag, length);
	//for (auto& item : hash_code) {
	//	std::cout << std::hex << (unsigned int)item << " ";
	//}
	//std::cout << std::endl;
	//std::cout << std::format("x:{}, y:{}, z:{}", recv_test_protocol->x(), recv_test_protocol->y(), recv_test_protocol->z()) << std::endl;
	//std::cout << std::endl;
}

#include <regex>
void DongkeyTest::RegexTest() {
	{
		std::regex regex("\\d{4}/(?:0?[1-9]|1[0-2])/(?:0?[1-9]|[1-2][0-9]|3[0-1])");
		while (true) {
			std::cout << "Enter a date(year/month/day) (q=quit): ";
			std::string str;
			if (!std::getline(std::cin, str) || str == "q") {
				break;
			}
			if (std::regex_match(str, regex)) {
				std::cout << "matched\n";
			}
			else {
				std::cout << "not matched\n";
			}
		}
	}
	{
		std::regex regex("[\\w]+");
		while (true) {
			std::cout << "Enter a string to split (q=quit): ";
			std::string str;
			if (!std::getline(std::cin, str) || str == "q") {
				break;
			}

			const std::sregex_iterator end;
			for (std::sregex_iterator itr(std::cbegin(str), std::cend(str), regex); itr != end; ++itr) {
				std::cout << "\"" << (*itr)[0] << "\"" << std::endl;
			}
		}
	}
	{
		std::regex regex("[l|L][o|O][v|V][e|E]");
		std::string const format("$1♡");
		while (true) {
			std::cout << "Enter a string to replace (q=quit): ";
			std::string str;
			if (!std::getline(std::cin, str) || str == "q") {
				break;
			}
			std::cout << std::regex_replace(str, regex, format) << std::endl;
		}
	}
	
	
}

class TestA {
public:
	int a;
	int b;
	int c;
};

class TestB {
public:
	int d;
	int f;
	int g;
};

class TestC : public TestA, public TestB {
public:
	auto operator<=>(TestC const&) const = default;
};

void DongkeyTest::Free()
{
	TestC a = { {.a = 1, .b = 2, .c = 3}, {.d = 4, .f = 5, .g = 6} };
}


UnitTest* DongkeyTest::Suite() {
	UnitTestSuite* suite = new UnitTestSuite("DongkeyTest");
	TUnitTest_AddTest(suite, DongkeyTest, Free);
	return suite;
}

