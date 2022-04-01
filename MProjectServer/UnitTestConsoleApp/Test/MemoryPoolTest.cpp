#include "MemoryPoolTest.h"
#include "GlobalDefine.h"
#include "UnitTest.h"

namespace {
	
	template<typename T>
	bool MemoryPoolTest(int n) {

	}

}

MemoryPoolTest::MemoryPoolTest(std::string const& _name) : UnitTestCase(_name) { ; }

MemoryPoolTest::~MemoryPoolTest() {

}

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

}

void MemoryPoolTest::MemoryPoolBenchmark()
{
}

void MemoryPoolTest::Setup()
{
}

void MemoryPoolTest::TearDown()
{
}

UnitTest* MemoryPoolTest::Suite()
{
	return nullptr;
}
