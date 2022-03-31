#pragma once
#include "MemoryPool.h"
#include "UnitTestCase.h"

class MemoryPoolTest : public UnitTestCase {
public:
	MemoryPoolTest(std::string const& _name);
	~MemoryPoolTest();

	void TestMemoryPool();
	void MemoryPoolBenchmark();

	virtual void Setup() override;
	virtual void TearDown() override;
	
	static UnitTest* Suite();
};

