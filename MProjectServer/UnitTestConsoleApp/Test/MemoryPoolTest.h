#pragma once
#include "Utility/MemoryPool.h"
#include "UnitTestCase.h"

class MemoryPoolTest : public UnitTestCase {
public:
	MemoryPoolTest(std::string const& _name);
	~MemoryPoolTest();

	void TestMemoryPool();
	void MemoryPoolBenchmark();

	
	static UnitTest* Suite();
};

