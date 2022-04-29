#pragma once
#include "UnitTestCase.h"

class DongkeyTest : public UnitTestCase {
public:
	DongkeyTest(std::string const& _name);
	~DongkeyTest();

	void MapTest();
	void MapBenchmark();

	void PacketTest();
	void RegexTest();

	static UnitTest* Suite();
};


