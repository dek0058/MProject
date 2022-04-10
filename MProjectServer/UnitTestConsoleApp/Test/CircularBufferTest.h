#pragma once
#include "UnitTestCase.h"
#include "Utility/CircularBuffer.h"
#include <memory>

class CircularBufferTest : public UnitTestCase {
public:
	CircularBufferTest(std::string const& _name);
	~CircularBufferTest();

	void Test();
	void TestCircularBufferTest();
	void CircularBufferTestBenchmark();

	static UnitTest* Suite();

	static std::unique_ptr<CircularBuffer_M> circular_buffer;
};

