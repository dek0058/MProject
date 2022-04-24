#pragma once
#include "UnitTestCase.h"

class DongkeyTest : public UnitTestCase {
public:
	DongkeyTest(std::string const& _name);
	~DongkeyTest();

	void MapTest();
	void FlatbuffersTest();
	void GenerateHashCodeTest();

	static UnitTest* Suite();
};


