#pragma once
#include "GuardDefine.h"
#include "UnitTest.h" /// include vector, string

class UnitTestResult;

class UnitTestSuite : public UnitTest {
	DELETE_REFERENCE_CREATOR(UnitTestSuite);

public:
	UnitTestSuite(const std::string _name = "") 
		: VAR_INIT(name) {; }
	~UnitTestSuite() {
		DeleteContents();
	}

	virtual void Run(UnitTestResult* _result) override;
	virtual int CountTestCases() const override;
	virtual std::string ToString() const override {
		return "suite " + name;
	}
	virtual UnitTest::Type GetType() const override {
		return UnitTest::Type::Suite;
	}

	void AddTest(UnitTest* _test) {
		tests.emplace_back(_test);
	}
	virtual void DeleteContents();
	std::vector<UnitTest*> const Tests() const {
		return tests;
	}

private:
	std::vector<UnitTest*> tests;
	std::string const name;
};
