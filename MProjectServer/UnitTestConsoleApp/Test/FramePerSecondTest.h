#pragma once
#include "UnitTestCase.h"

class FramePerSecondTest : public UnitTestCase {
public:
	FramePerSecondTest(std::string const& _name);
	~FramePerSecondTest();

	void TestFramePerSecond();

	static UnitTest* Suite();
};


