#include "UnitTestSuite.h"
#include "UnitTestResult.h"

void UnitTestSuite::Run(UnitTestResult* _result) {
	for (auto& iter : tests) {
		if (_result->ShouldStop()) {
			break;
		}
		if (false == Setup().empty()) {
			iter->AddSetup(Setup());
		}
		iter->Run(_result);
	}
}

int UnitTestSuite::CountTestCases() const {
	int count = 0;
	for (auto& iter : tests) {
		count += iter->CountTestCases();
	}
	return count;
}

void UnitTestSuite::DeleteContents() {
	for (std::vector<UnitTest*>::iterator iter = tests.begin(); iter != tests.end(); ++iter) {
		delete* iter;
	}
}
