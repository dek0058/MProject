#include "DongkeyUnitTestSuite.h"
#include "UnitTestSuite.h"

// Test
#include "Test/FramePerSecondTest.h"
#include "Test/DongkeyTest.h"

UnitTest* DongkeyUnitTestSuite::Suite() {
	UnitTestSuite* suite = new UnitTestSuite("DongkeyUnitTestSuite");
	
	//suite->AddTest(FramePerSecondTest::Suite());
	suite->AddTest(DongkeyTest::Suite());

	return suite;
}