#include "UnitTestCase.h"
#include "UnitTestResult.h"
#include "Exception/BaseException.h"

#include <iostream>
#include <stdexcept>
#include <format>


void UnitTestCase::Run(UnitTestResult* _result) {
	_result->StartTest(this);
	Setup();
	try {
		RunTest();
	} catch (BaseException<2>& _exception) {
		_result->AddFailure(this, new BaseException(_exception));
	} catch (std::exception& _exception) {
		_result->AddError(this, new BaseException(std::format("{}: {}", typeid(_exception).name(), _exception.what())));
	} catch(...) {
		_result->AddError(this, new BaseException("unknown exception"));

	}
	TearDown();
	_result->EndTest(this);
}

UnitTestResult* UnitTestCase::Run() {
	UnitTestResult* result = DefaultResult();
	Run(result);
	return result;
}

UnitTestResult* UnitTestCase::DefaultResult() {
	return new UnitTestResult;
}

void UnitTestCase::AssertImplementation(bool _condition, std::string const& _condition_expression, long _line_num, std::string const& _file_name) {
	if (false == _condition) {
		throw BaseException(_condition_expression, _line_num, _file_name);
	}
}

void UnitTestCase::Loop1AssertImplementation(bool _condition, std::string const& _condition_expression, long _line_num, long _data_line_num, std::string const& _file_name) {
	if (false == _condition) {
		throw BaseException(_condition_expression, _line_num, _data_line_num, _file_name);
	}
}

void UnitTestCase::Loop2AssertImplementation(bool _condition, std::string const& _condition_expression, long _line_num, long _data1_line_num, long _data2_line_num, std::string const& _file_name) {
	if (false == _condition) {
		throw BaseException(_condition_expression, _line_num, _data1_line_num, _data2_line_num, _file_name);
	}
}

void UnitTestCase::AssertEquals(long _expected, long _actual, long _line_num, std::string const& _file_name) {
	if (_expected != _actual) {
		AssertImplementation(false, NotEqualsMessage(_expected, _actual), _line_num, _file_name);
	}
}

void UnitTestCase::AssertEquals(long _expected, long _actual, long delta, long _line_num, std::string const& _file_name) {
	if (fabs(_expected - _actual) > delta) {
		AssertImplementation(false, NotEqualsMessage(_expected, _actual), _line_num, _file_name);
	}
}

void UnitTestCase::AssertEquals(std::string const& _expected, std::string const& _actual, long _line_num, std::string const& _file_name) {
	if (_expected != _actual) {
		AssertImplementation(false, NotEqualsMessage(_expected, _actual), _line_num, _file_name);
	}
}

void UnitTestCase::AssertEquals(void const* _expected, void const* _actual, long _line_num, std::string const& _file_name) {
	if (_expected != _actual) {
		AssertImplementation(false, NotEqualsMessage(_expected, _actual), _line_num, _file_name);
	}
}

std::string UnitTestCase::NotEqualsMessage(long _expected, long _actual) {
	return std::format("expected: {} but was: {}", _expected, _actual);
}

std::string UnitTestCase::NotEqualsMessage(double _expected, double _actual) {
	return std::format("expected: {} but was: {}", _expected, _actual);
}

std::string UnitTestCase::NotEqualsMessage(void const* _expected, void const* _actual) {
	return std::format("expected: {} but was: {}", _expected, _actual);
}

std::string UnitTestCase::NotEqualsMessage(std::string const& _expected, std::string const& _actual) {
	return std::format("expected: \"{}\" but was: \"{}\"", _expected, _actual);
}

void UnitTestCase::AssertNotNull(void const* _ptr, std::string const& _ptr_expression, long _line_num, std::string const& _file_name) {
	if (_ptr == nullptr) {
		throw BaseException(_ptr_expression + " must not be nullptr.", _line_num, _file_name);
	}
}

void UnitTestCase::AssertNull(void const* _ptr, std::string const& _ptr_expression, long _line_num, std::string const& _file_name) {
	if (_ptr != nullptr) {
		throw BaseException(_ptr_expression + " must not be nullptr.", _line_num, _file_name);
	}
}

void UnitTestCase::Fail(std::string const& _message, long _line_num, std::string const& _file_name) {
	throw BaseException(std::string("fail: ") + _message, _line_num, _file_name);
}

void UnitTestCase::Warning(std::string const& _message, long _line_num, std::string const& _file_name) {
	std::cout << std::format("Warning [{}:{}]: {}\n", _file_name, _line_num, _message);
}
