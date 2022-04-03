#pragma once
#include <vector>
#include <string>

class UnitTestResult;

class UnitTest {
public:
	enum class Type : unsigned char {
		Suite = 0,
		Normal = 1,
		Long = 2
	};

public:
	virtual ~UnitTest() { ; }
	virtual void Run(UnitTestResult* _result) { ; }
	virtual int CountTestCases() const { 
		return 0; 
	}
	virtual std::string ToString() const {
		return "";
	}
	virtual UnitTest::Type GetType() const {
		return Type::Normal;
	}

	void AddSetup(std::vector<std::string> const& _setup) {
		setup = _setup;
	}
	std::vector<std::string> const& Setup() const {
		return setup;
	}

private:
	std::vector<std::string> setup;
};

