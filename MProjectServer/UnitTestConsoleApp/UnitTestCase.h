#pragma once
#include <string>
#include <exception>
#include <typeinfo>

#include "GuardDefine.h"
#include "UnitTest.h"

class UnitTestResult;

class UnitTestCase : public UnitTest {
	DELETE_REFERENCE_CREATOR(UnitTestCase)

public:
	UnitTestCase(std::string const& _name, UnitTest::Type _type = UnitTest::Type::Normal) : name(_name) {
		SetType(_type);
	}
	~UnitTestCase() { ; }

	virtual void Run(UnitTestResult* _result);
	virtual UnitTestResult* Run();
	virtual int CountTestCases() const {
		return 1;
	}
	virtual std::string ToString() const {
		std::type_info const& this_class = typeid(*this);
		return std::string(this_class.name()) + "." + Name();
	}
	virtual UnitTest::Type GetType() const {
		return type;
	}
	void SetType(UnitTest::Type _type) {
		type = _type;
	}
	std::string const& Name() const {
		return name;
	}

protected:
	virtual void RunTest();
	UnitTestResult* DefaultResult();

	void AssetImplementation(bool _condition, std::string const& _condition_expression = "", long _line_num = 0, std::string const& _file_name = "");
	void Loop1AssetImplementation(bool _condition, std::string const& _condition_expression = "", long _line_num = 0, long _data_line_num = 0, std::string const& _file_name = "");
	void Loop2AssetImplementation(bool _condition, std::string const& _condition_expression = "", long _line_num = 0, long _data1_line_num = 0, long _data2_line_num = 0, std::string const& _file_name = "");
	
	void AssetEquals(long _expected, long _actual, long _line_num = 0, std::string const& _file_name = "");
	void AssetEquals(long _expected, long _actual, long delta, long _line_num = 0, std::string const& _file_name = "");
	void AssetEquals(std::string const& _expected, std::string const& _actual, long _line_num = 0, std::string const& _file_name = "");
	void AssetEquals(void const* _expected, void const* _actual, long _line_num = 0, std::string const& _file_name = "");
	
	std::string NotEqualsMessage(long _expected, long _actual);
	std::string NotEqualsMessage(double _expected, double _actual);
	std::string NotEqualsMessage(void const* _expected, void const* _actual);
	std::string NotEqualsMessage(std::string const& _expected, std::string const& _actual);

	void AssertNotNull(void const* _ptr, std::string const& _ptr_expression = "", long _line_num = 0, std::string const& _file_name = "");
	void AssertNull(void const* _ptr, std::string const& _ptr_expression = "", long _line_num = 0, std::string const& _file_name = "");

	void Fail(std::string const& _message, long _line_num = 0, std::string const& _file_name = "");
	void Warning(std::string const& _message, long _line_num = 0, std::string const& _file_name = "");

private:
	std::string name;
	UnitTest::Type type;
};