#pragma once
#include "UnitTestCase.h"
#include "Utility/SPSCQueue.h"

class SPSCQueueTest : public UnitTestCase {
public:
	SPSCQueueTest(std::string const& _name);
	~SPSCQueueTest();

	void TestSPSCQueue();
	void SPSCQueueBenchmark();

	static UnitTest* Suite();
};

