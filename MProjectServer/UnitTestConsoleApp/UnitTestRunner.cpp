#include "UnitTestRunner.h"
#include "UnitTest.h"
#include "UnitTestSuite.h"
#include "TextUnitTestResult.h"

#include <iostream>
#include <format>


UnitTestRunner::UnitTestRunner() : ostream(std::cout) { ; }

UnitTestRunner::UnitTestRunner(std::ostream& _ostream) : ostream(_ostream) { ; }

UnitTestRunner::~UnitTestRunner() {
	for (Mappings::iterator it = mappings.begin(); it != mappings.end(); ++it) {
		delete it->second;
	}
}

bool UnitTestRunner::Run(std::vector<std::string> const& _args) {
	std::string test_case;
	int num_of_tests = 0;
	bool success = true;
	bool all = false;
	bool wait = false;
	bool printed = false;
	bool long_running = false;
	std::string ignore;

	std::vector<std::string> setup;
	std::vector<UnitTest*> tests;

	for (int i = 1; i < _args.size(); ++i) {
		std::string const& arg = _args[i];
		if (arg.compare("-wait") == 0) {
			wait = true;
		} else if (arg.compare("-all") == 0) {
			all = true;
		} else if(arg.compare("-long") == 0) {
			long_running = true;
		} else if(arg.compare("-ignore") == 0) {
			ignore = arg[++i];
		} else if(arg.compare("-print") == 0) {
			for (Mappings::iterator it = mappings.begin(); it != mappings.end(); ++it) {
				Print(it->first, it->second, 0);
			}
			printed = true;
		} else if(arg.compare("-setup") == 0) {
			if ((i + 1) < static_cast<int>(_args.size())) {
				setup.emplace_back(_args[++i]);
			}
		} else {
			if (false == all) {
				test_case = arg;
				if (true == test_case.empty()) {
					PrintBanner();
					return false;
				}

				UnitTest* test = nullptr;
				for (Mappings::iterator it = mappings.begin(); it != mappings.end(); ++it) {
					test = Find(test_case, it->second, it->first);
				}
				if (nullptr != test) {
					CollectAllTestCases(test, tests);
				}
				if (nullptr == test) {
					ostream << std::format("Test {} not found.\n", test_case);
					return false;
				}
			}
		}
	}

	if (true == all) {
		tests.clear();
		for (auto& mapping : mappings) {
			CollectAllTestCases(mapping.second, tests);
		}
	}

	TextUnitTestResult result(ostream, ignore);
	for (auto& test : tests) {
		if (test->GetType() == UnitTest::Type::Long && false == long_running) {
			continue;
		}
		if (setup.size() > 0) {
			test->AddSetup(setup);
		}
		test->Run(&result);
		++num_of_tests;
	}

	ostream << result << std::endl;
	success = result.WasSuccessful();

	if (num_of_tests == 0 && false == printed) {
		PrintBanner();
		return false;
	}

	if (true == wait) {
		ostream << "<RETURN> to continue" << std::endl;
		std::cin.get();
	}

	return success;
}

void UnitTestRunner::AddTest(std::string const& _name, UnitTest* _test) {
	mappings.emplace_back(Mapping(_name, _test));
}

void UnitTestRunner::PrintBanner() {
	ostream << "Usage: driver [-all] [-ignore <file>] [-long] [-print] [-wait] [name] ...\n"
			<< "       where name is the name of a test case class" << std::endl;
}

void UnitTestRunner::Print(std::string const& _name, UnitTest* _test, int indent) {
	for (int i = 0; i < indent; ++i) {
		ostream << "    ";
	}
	ostream << _name << std::endl;
	UnitTestSuite* suite = dynamic_cast<UnitTestSuite*>(_test);
	if (nullptr != suite) {
		std::vector<UnitTest*> const& tests = suite->Tests();
		for (auto& test : tests) {
			Print(test->ToString(), test, indent + 1);
		}
	}
}

UnitTest* UnitTestRunner::Find(std::string const& _name, UnitTest* _test, std::string const& _test_name) {
	if (_test_name.find(_name) != std::string::npos) {
		return _test;
	} else {
		UnitTestSuite* suite = dynamic_cast<UnitTestSuite*>(_test);
		if (nullptr != suite) {
			std::vector<UnitTest*> const& tests = suite->Tests();
			for (auto& test : tests) {
				UnitTest* result = Find(_name, test, test->ToString());
				if (nullptr != result) {
					return result;
				}
			}
		}
		return nullptr;
	}
}

int UnitTestRunner::CollectAllTestCases(UnitTest* _test, std::vector<UnitTest*>& _tests) {
	int added = 0;
	if (_test->GetType() == UnitTest::Type::Suite) {
		UnitTestSuite* suite = dynamic_cast<UnitTestSuite*>(_test);
		if (nullptr != suite) {
			std::vector<UnitTest*> const& tests = suite->Tests();
			for (auto& test : tests) {
				added += CollectAllTestCases(test, _tests);
			}
		}
	}
	else {
		_tests.emplace_back(_test);
		added = 1;
	}
	return added;
}
