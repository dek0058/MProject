#pragma once
#include "UnitTestResult.h"

#include <ostream>
#include <set>

class TextUnitTestResult : public UnitTestResult {
public:
	TextUnitTestResult();
	TextUnitTestResult(std::string const& _ignore);
	TextUnitTestResult(std::ostream& _ostream);
	TextUnitTestResult(std::ostream& _ostream, std::string const& _ignore);

	virtual void AddError(UnitTest* _test, BaseException* _exception) override;
	virtual void AddFailure(UnitTest* _test, BaseException* _exception) override;
	virtual void StartTest(UnitTest* _test) override;

	virtual void Print(std::ostream& _ostream);
	virtual void PrintErrors(std::ostream& _ostream);
	virtual void PrintFailures(std::ostream& _ostream);
	virtual void PrintHeader(std::ostream& _ostream);

protected:
	std::string ShortName(std::string const& _test_name);
	void Setup();
	void Ignoring(std::string const _ignore);

private:
	std::ostream& ostream;
	std::set<std::string> ignored;
};

inline std::ostream& operator<< (std::ostream& _ostream, TextUnitTestResult& _result) {
	_result.Print(_ostream);
	return _ostream;
}
