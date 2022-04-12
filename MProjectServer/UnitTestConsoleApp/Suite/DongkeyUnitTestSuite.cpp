#include "DongkeyUnitTestSuite.h"
#include "UnitTestSuite.h"

// Test
#include "Test/FramePerSecondTest.h"

UnitTest* DongkeyUnitTestSuite::Suite() {
	UnitTestSuite* suite = new UnitTestSuite("DongkeyUnitTestSuite");

	suite->AddTest(FramePerSecondTest::Suite());

	return suite;
}