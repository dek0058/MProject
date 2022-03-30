#pragma once
#include <vector>

class UnitTestResult;

class UnitTest {
public:
	enum Type {
		Suite,
		Normal,
		Long
	};

public:
	virtual ~UnitTest() = 0;
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

