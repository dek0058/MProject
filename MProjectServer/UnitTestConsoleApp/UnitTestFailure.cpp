#include "UnitTestFailure.h"
#include "UnitTest.h"

std::string UnitTestFailure::ToString() {
	return "None";
	//return failed_test->ToString() << ": " << thrown_exception->what();
}