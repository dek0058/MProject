#include "FramePerSecondTest.h"
#include "UnitTestSuite.h"
#include "UnitTestCaller.h"

#include "Utility/MThread.h"

FramePerSecondTest::FramePerSecondTest(std::string const& _name) : UnitTestCase(_name) { ; }

FramePerSecondTest::~FramePerSecondTest() { ; }

void FramePerSecondTest::TestFramePerSecond() {
	
}

UnitTest* FramePerSecondTest::Suite() {
	UnitTestSuite* suite = new UnitTestSuite("FramePerSecondTest");
	TUnitTest_AddTest(suite, FramePerSecondTest, TestFramePerSecond);
	return suite;
}
