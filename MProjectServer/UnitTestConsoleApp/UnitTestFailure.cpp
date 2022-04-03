#include "UnitTestFailure.h"
#include "UnitTest.h"

std::string UnitTestFailure::ToString() {
	return failed_test->ToString() + ": " + exception->what();
}