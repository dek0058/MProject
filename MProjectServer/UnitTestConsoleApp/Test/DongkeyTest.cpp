#include "DongkeyTest.h"
#include "UnitTestSuite.h"
#include "UnitTestCaller.h"

#include <iostream>
#include <string>
#include <map>

DongkeyTest::DongkeyTest(std::string const& _name) : UnitTestCase(_name) {
}

DongkeyTest::~DongkeyTest() {
}

void DongkeyTest::TestMap() {
	std::cout << std::endl;
	std::map<int, std::string> string_map{ {1, "A"}, {2, "B"}, {3, "C"}, {5, "F"} };

	auto test_i = string_map[4]; // create or find
	
	for (auto& pair : string_map) {
		std::cout << pair.first << " : " << pair.second << std::endl;
	}
}

UnitTest* DongkeyTest::Suite() {
	UnitTestSuite* suite = new UnitTestSuite("DongkeyTest");
	TUnitTest_AddTest(suite, DongkeyTest, TestMap);
	return suite;
}

