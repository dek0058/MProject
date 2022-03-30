#include "MemoryPoolTest.h"
#include "GlobalDefine.h"

void MemoryPoolTest::Test() {
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