#include "MemoryPoolTest.h"
#include "GlobalDefine.h"
#include "UnitTest.h"
#include "UnitTestSuite.h"
#include "UnitTestCaller.h"

namespace {
	
	template<typename T>
	bool IsTest(int n) {
		bool result = true;
		std::vector<T*> vector(n, nullptr);
		MemoryPool<T> memory_pool(sizeof(T*), vector.size() / 2);
		for (int i = 0; i < vector.size(); ++i) {
			vector[i] = new (memory_pool.Get()) (T)(i);
		}
		for (int i = 0; i < vector.size(); ++i) {
			result = result && (nullptr != vector[i] && *vector[i] == i);
		}
		for (int i = 0; i < vector.size(); ++i) {
			memory_pool.Release(vector[i]);
		}
		return result;
	}

}

MemoryPoolTest::MemoryPoolTest(std::string const& _name) : UnitTestCase(_name) { ; }

MemoryPoolTest::~MemoryPoolTest() {

}

template<typename T>
struct FBlock {
	FBlock() {
		memory.next = this + 1;
	}
	explicit FBlock(FBlock* _next) {
		memory.next = _next;
	}
	union {
		char buffer[sizeof(T)];
		FBlock* next;
	} memory;
private:
	FBlock(FBlock const&) = delete;
	FBlock& operator = (FBlock const&) = delete;
};

void MemoryPoolTest::TestMemoryPool() {
	int blocks = 10;
	MemoryPool<int> int_pool(blocks);

	std::vector<int*> int_vector(blocks, nullptr);

	for (int i = 0; i < blocks; ++i) {
		int_vector[i] = new (int_pool.Get()) (int)(i);
	}

	for (int i = 0; i < blocks; ++i) {
		TAssert_True(int_vector[i] && *int_vector[i] == i);
	}

	for (int i = 0; i < blocks; ++i) {
		int_pool.Release(int_vector[i]);
	}

	int sz = 5;
	TAssert_True(IsTest<char>(sz));
	TAssert_True(IsTest<signed char>(sz));
	TAssert_True(IsTest<byte>(sz));
	TAssert_True(IsTest<short>(sz));
	TAssert_True(IsTest<ushort>(sz));
	TAssert_True(IsTest<int>(sz));
	TAssert_True(IsTest<uint>(sz));
	TAssert_True(IsTest<long>(sz));
	TAssert_True(IsTest<ulong>(sz));

	int const elements = 16;
	MemoryPool<char[elements]> char_pool(blocks);
	char* ptr = reinterpret_cast<char*>(char_pool.Get());
	char const* test_msg = "1234567890abcde";//15 + '\0' = 16 size
	std::memcpy(ptr, test_msg, elements);
	
	TAssert_True(std::string(ptr).length() == elements - 1);
	TAssert_True(std::strcmp(ptr, test_msg) == 0);
	char_pool.Release(ptr);
}

void MemoryPoolTest::MemoryPoolBenchmark() {

}

void MemoryPoolTest::Setup()
{
}

void MemoryPoolTest::TearDown()
{
}

UnitTest* MemoryPoolTest::Suite()
{
	UnitTestSuite* suite = new UnitTestSuite("MemoryPoolTest");
	TUnitTest_AddTest(suite, MemoryPoolTest, TestMemoryPool);
	return suite;
}
