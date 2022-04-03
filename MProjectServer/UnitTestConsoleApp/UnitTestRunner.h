#pragma once
#include <ostream>
#include <string>
#include <vector>
#include <utility>



class UnitTest;

class UnitTestRunner {
	using Mapping = std::pair<std::string, UnitTest*>;
	using Mappings = std::vector<Mapping>;

public:
	UnitTestRunner();
	UnitTestRunner(std::ostream& _ostream);
	~UnitTestRunner();

	bool Run(std::vector<std::string> const& _args);
	void AddTest(std::string const& _name, UnitTest* _test);

protected:
	void PrintBanner();
	void Print(std::string const& _name, UnitTest* _test, int indent);
	UnitTest* Find(std::string const& _name, UnitTest* _test, std::string const& _test_name);
	int CollectAllTestCases(UnitTest* _test, std::vector<UnitTest*>& _tests);

private:
	std::ostream& ostream;
	Mappings mappings;
};
