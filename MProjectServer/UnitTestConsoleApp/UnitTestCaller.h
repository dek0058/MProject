#pragma once

#include "UnitTestCase.h"

#include <memory>

template<class Fixture>
class UnitTestCaller : public UnitTestCase {
	DELETE_REFERENCE_CREATOR(UnitTestCaller);

	typedef void (Fixture::*TestMethod)();

public:
	UnitTestCaller(std::string const& _name, TestMethod _test, UnitTest::Type _type = UnitTest::Type::Normal)
		: UnitTestCase(_name, _type), VAR_INIT(test), fixture(new Fixture(_name)) { ; }

protected:
	virtual void RunTest() override {
		(fixture.get()->*test)();
	}

	virtual void Setup() override {
		if (false == UnitTest::Setup().empty()) {
			fixture.get()->AddSetup(UnitTest::Setup());
		}
		fixture.get()->Setup();
	}

	virtual void TearDown() override {
		fixture.get()->TearDown();
	}

private:
	TestMethod test;
	std::unique_ptr<Fixture> fixture;
};

#define TUnitTest_AddTest(suite, cls, mth) \
	suite->AddTest(new UnitTestCaller<cls>(#mth, &cls::mth))

#define TUnitTest_AddLongTest(suite, cls, mth) \
	suite->AddTest(new UnitTestCaller<cls>(#mth, &cls::mth, UnitTest::Type::Long))

#define TUnitTest_AddQualifiedTest(suite, cls, mth) \
	suite->AddTest(new UnitTestCaller<cls>(#cls"::"#mth, &cls::mth))

#define TUnitTest_AddLongQualifiedTest(suite, cls, mth) \
	suite->AddTest(new UnitTestCaller<cls>(#cls"::"#mth, &cls::mth, UnitTest::Type::Long))

