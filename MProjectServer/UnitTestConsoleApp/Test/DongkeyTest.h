#pragma once
#include "UnitTestCase.h"

class DongkeyTest : public UnitTestCase {
public:
	DongkeyTest(std::string const& _name);
	~DongkeyTest();

	static UnitTest* Suite();
};


