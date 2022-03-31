#include "MemoryPoolTest.h"
#include "GlobalDefine.h"
#include "UnitTest.h"


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
		int_pool.Release(int_vector[i]);
	}
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
