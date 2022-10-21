#pragma once
#include "UnitTestCase.h"

class DongkeyTest : public UnitTestCase {
public:
	DongkeyTest(std::string const& _name);
	~DongkeyTest();

	// Cast Test
	void TestCast();

	void TestJThread();


	static UnitTest* Suite();
};


