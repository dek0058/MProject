#include "CoreUnitTestSuite.h"
#include "UnitTestSuite.h"

// Test
#include "Test/MemoryPoolTest.h"
#include "Test/SPSCQueueTest.h"
#include "Test/CircularBufferTest.h"

UnitTest* CoreUnitTestSuite::Suite() {
	UnitTestSuite* suite = new UnitTestSuite("CoreTestSuite");

	suite->AddTest(MemoryPoolTest::Suite());
	suite->AddTest(SPSCQueueTest::Suite());
	suite->AddTest(CircularBufferTest::Suite());

	return suite;
}