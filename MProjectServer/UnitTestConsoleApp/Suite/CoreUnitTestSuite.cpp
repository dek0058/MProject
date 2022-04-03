#include "CoreUnitTestSuite.h"
#include "UnitTestSuite.h"

// Test
#include "Test/MemoryPoolTest.h"

UnitTest* CoreUnitTestSuite::Suite() {
	UnitTestSuite* suite = new UnitTestSuite("CoreTestSuite");

	suite->AddTest(MemoryPoolTest::Suite());

	return suite;
}