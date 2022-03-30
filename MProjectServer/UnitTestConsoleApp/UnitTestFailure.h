#pragma once
#include <exception>
#include <string>

#include "GuardDefine.h"

class UnitTest;

class UnitTestFailure {
	DELETE_REFERENCE_CREATOR(UnitTestFailure)

public:
	UnitTestFailure(UnitTest* _failed_test, std::exception* _exception)
		: failed_test(_failed_test), thrown_exception(_exception) { ; }
	~UnitTestFailure() {
		delete thrown_exception;
	}

	UnitTest* FailedTest() {
		return failed_test;
	}
	std::exception* ThrownException() {
		return thrown_exception;
	}
	std::string ToString();

protected:
	UnitTest* failed_test;
	std::exception* thrown_exception;
};