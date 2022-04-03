#pragma once
#include <exception>
#include <string>

#include "GuardDefine.h"
#include "Exception/BaseException.h"

class UnitTest;

class UnitTestFailure {
	DELETE_REFERENCE_CREATOR(UnitTestFailure)

public:
	UnitTestFailure(UnitTest* _failed_test, BaseException* _exception)
		: VAR_INIT(failed_test), VAR_INIT(exception) { ; }
	~UnitTestFailure() {
		delete exception;
	}

	UnitTest* FailedTest() {
		return failed_test;
	}
	BaseException* ThrownException() {
		return exception;
	}
	std::string ToString();

protected:
	UnitTest* failed_test;
	BaseException* exception;
};