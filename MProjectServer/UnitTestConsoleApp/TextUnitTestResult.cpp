#include "TextUnitTestResult.h"
#include "UnitTest.h"
#include "BaseException.h"

#include <iostream>
#include <fstream>
#include <format>
#include <iomanip>

TextUnitTestResult::TextUnitTestResult() : ostream(std::cout) { ; }

TextUnitTestResult::TextUnitTestResult(std::string const& _ignore) : ostream(std::cout) {
	if (true == _ignore.empty()) {
		Setup();
		return;
	}

	try {
		std::ifstream ifstream(_ignore);
		if (true == ifstream.is_open()) {
			char line[256];
			while (ifstream.getline(line, sizeof(line))) {
				if (line[0] == '#') {
					continue;
				}
				std::string ignored(line);
				Ignoring(ignored);
			}
			ifstream.close();
		}
	} catch(std::exception _exception) {
		std::cout << _exception.what() << std::endl;
	}

	Setup();
}

TextUnitTestResult::TextUnitTestResult(std::ostream& _ostream) : VAR_INIT(ostream) { ; }

TextUnitTestResult::TextUnitTestResult(std::ostream& _ostream, std::string const& _ignore) 
	: VAR_INIT(ostream) {
	if (true == _ignore.empty()) {
		Setup();
		return;
	}

	try {
		std::ifstream ifstream(_ignore);
		if (true == ifstream.is_open()) {
			char line[256];
			while (ifstream.getline(line, sizeof(line))) {
				if (line[0] == '#') {
					continue;
				}
				std::string ignored(line);
				Ignoring(ignored);
			}
			ifstream.close();
		}
	}
	catch (std::exception _exception) {
		std::cout << _exception.what() << std::endl;
	}

	Setup();
}

void TextUnitTestResult::AddError(UnitTest* _test, BaseException* _exception) {
	if (ignored.find(_test->ToString()) == ignored.end()) {
		UnitTestResult::AddError(_test, _exception);
		ostream << "ERROR" << std::flush;
	} else {
		ostream << "ERROR (ignored)" << std::flush;
		delete _exception;
	}
}

void TextUnitTestResult::AddFailure(UnitTest* _test, BaseException* _exception) {
	if (ignored.find(_test->ToString()) == ignored.end()) {
		UnitTestResult::AddFailure(_test, _exception);
		ostream << "FAILURE" << std::flush;
	}
	else {
		ostream << "FAILURE (ignored)" << std::flush;
		delete _exception;
	}
}

void TextUnitTestResult::StartTest(UnitTest* _test) {
	UnitTestResult::StartTest(_test);
	ostream << "\n" << ShortName(_test->ToString()) << ": " << std::flush;
}

void TextUnitTestResult::Print(std::ostream& _ostream) {
	PrintHeader(_ostream);
	PrintErrors(_ostream);
	PrintFailures(_ostream);
}

void TextUnitTestResult::PrintErrors(std::ostream& _ostream) {
	if (TestErrors() != 0) {
		_ostream << "\n";

		if (TestErrors() == 1) {
			_ostream << std::format("There was {} error: ", TestErrors()) << std::endl;
		} else {
			_ostream << std::format("There were {} errors: ", TestErrors()) << std::endl;
		}

		int i = 1;
		for (auto& failure : Errors()) {
			BaseException* exception = failure->ThrownException();

			_ostream << std::setw(2) << i
				<< ": "
				<< failure->FailedTest()->ToString() << "\n"
				<< "    \"" << (nullptr != exception ? exception->what() : "") << "\"\n"
				<< "    in\""
				<< (nullptr != exception ? exception->GetFileNmae() : std::string())
				<< "\", line ";

			if (exception == nullptr) {
				_ostream << "nullptr";
			} else {
				_ostream << exception->GetLineNumber();
				if (exception->GetDataLineNumber(1) != Unknown_Line_Number) {
					_ostream << "data liens " << exception->GetDataLineNumber() << ", " << exception->GetDataLineNumber(1);
				} else if(exception->GetDataLineNumber() != Unknown_Line_Number) {
					_ostream << " data line " << exception->GetDataLineNumber();
				}
			}
			_ostream << std::endl;
			++i;
		}
	}
}

void TextUnitTestResult::PrintFailures(std::ostream& _ostream) {
	if (TestFailures() != 0) {
		_ostream << "\n";

		if (TestFailures() == 1) {
			_ostream << std::format("There was {} failure: ", TestFailures()) << std::endl;
		}
		else {
			_ostream << std::format("There were {} failures: ", TestFailures()) << std::endl;
		}

		int i = 1;
		for (auto& failure : Failures()) {
			BaseException* exception = failure->ThrownException();

			_ostream << std::setw(2) << i
				<< ": "
				<< failure->FailedTest()->ToString() << "\n"
				<< "    \"" << (nullptr != exception ? exception->what() : "") << "\"\n"
				<< "    in\""
				<< (nullptr != exception ? exception->GetFileNmae() : std::string())
				<< "\", line ";

			if (exception == nullptr) {
				_ostream << "nullptr";
			}
			else {
				_ostream << exception->GetLineNumber();
				if (exception->GetDataLineNumber(1) != Unknown_Line_Number) {
					_ostream << "data liens " << exception->GetDataLineNumber() << ", " << exception->GetDataLineNumber(1);
				}
				else if (exception->GetDataLineNumber() != Unknown_Line_Number) {
					_ostream << " data line " << exception->GetDataLineNumber();
				}
			}
			_ostream << std::endl;
			++i;
		}
	}
}

void TextUnitTestResult::PrintHeader(std::ostream& _ostream) {
	_ostream << "\n\n";
	if (true == WasSuccessful()) {
		_ostream << "OK (" << RunTests() << " tests)" << std::endl;
	} else {
		_ostream << "[실패]" << "\n" << "Runs: " << RunTests() << "   Failures:" << TestFailures() << "   Errors: " << TestErrors() << std::endl;
	}
}

std::string TextUnitTestResult::ShortName(std::string const& _test_name) {
	std::string::size_type pos = _test_name.rfind('.');
	if (pos != std::string::npos) {
		return std::string(_test_name, pos + 1);
	} else {
		return _test_name;
	}
}

void TextUnitTestResult::Setup() {
	char const* env = std::getenv("IGNORE");
	if (nullptr != env) {
		std::string ignored = env;
		Ignoring(env);
	}
}

void TextUnitTestResult::Ignoring(std::string const _ignore) {
	std::string::const_iterator it = _ignore.begin();
	std::string::const_iterator end = _ignore.end();
	while (true) {
		while (it != end && (std::isspace(*it) || *it == '"' || *it == ',' || *it == '\'')) {
			++it;
		}
		if (it == end) {
			break;
		}
		std::string test;
		while (it != end && *it != ',' && *it != '"' && *it != '\'') {
			test += *it++;
		}
		if (false == test.empty()) {
			ignored.insert(test.erase(test.find_last_not_of(" \n\r\t") + 1));
		}
	}
}
