#include "UnitTestCase.h"
#include "UnitTestResult.h"

void UnitTestCase::Run(UnitTestResult* _result) {
	_result->StartTest(this);
	Setup();
	try {

	}
	catch (...) {

	}
	_result->EndTest(this);
}

UnitTestResult* UnitTestCase::Run()
{
	return nullptr;
}

UnitTestResult* UnitTestCase::DefaultResult()
{
	return nullptr;
}

void UnitTestCase::AssetImplementation(bool _condition, std::string const& _condition_expression, long _line_num, std::string const& _file_name)
{
}

void UnitTestCase::Loop1AssetImplementation(bool _condition, std::string const& _condition_expression, long _line_num, long _data_line_num, std::string const& _file_name)
{
}

void UnitTestCase::Loop2AssetImplementation(bool _condition, std::string const& _condition_expression, long _line_num, long _data1_line_num, long _data2_line_num, std::string const& _file_name)
{
}

void UnitTestCase::AssetEquals(long _expected, long _actual, long _line_num, std::string const& _file_name)
{
}

void UnitTestCase::AssetEquals(long _expected, long _actual, long delta, long _line_num, std::string const& _file_name)
{
}

void UnitTestCase::AssetEquals(std::string const& _expected, std::string const& _actual, long _line_num, std::string const& _file_name)
{
}

void UnitTestCase::AssetEquals(void const* _expected, void const* _actual, long _line_num, std::string const& _file_name)
{
}

std::string UnitTestCase::NotEqualsMessage(long _expected, long _actual)
{
	return std::string();
}

std::string UnitTestCase::NotEqualsMessage(double _expected, double _actual)
{
	return std::string();
}

std::string UnitTestCase::NotEqualsMessage(void const* _expected, void const* _actual)
{
	return std::string();
}

std::string UnitTestCase::NotEqualsMessage(std::string const& _expected, std::string const& _actual)
{
	return std::string();
}

void UnitTestCase::AssertNotNull(void const* _ptr, std::string const& _ptr_expression, long _line_num, std::string const& _file_name)
{
}

void UnitTestCase::AssertNull(void const* _ptr, std::string const& _ptr_expression, long _line_num, std::string const& _file_name)
{
}

void UnitTestCase::Fail(std::string const& _message, long _line_num, std::string const& _file_name)
{
}

void UnitTestCase::Warning(std::string const& _message, long _line_num, std::string const& _file_name)
{
}
