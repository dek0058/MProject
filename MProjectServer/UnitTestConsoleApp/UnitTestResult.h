#pragma once
#include <exception>
#include <vector>

#include "UnitTestFailure.h"
#include "Exception/BaseException.h"

class UnitTest;

class UnitTestResult {
public:
	struct FSyncObject {
		FSyncObject() { ; }
		virtual ~FSyncObject() { ; }
		virtual void Lock() { ; }
		virtual void Unlock() { ; }
	};

	struct FExclusiveZone {
		FExclusiveZone(FSyncObject* _sync_obj) : sync_obj(_sync_obj) {
			sync_obj->Lock();
		}
		~FExclusiveZone() {
			sync_obj->Unlock();
		}
	private:
		FSyncObject* sync_obj;
	};

public:
	UnitTestResult() : run_tests(0), stop(false), sync_obj(new FSyncObject()) { ; }
	virtual ~UnitTestResult() { ; }
	
	virtual void AddError(UnitTest* _test, BaseException* _exception) {
		FExclusiveZone zone(sync_obj);
		errors.emplace_back(new UnitTestFailure(_test, _exception));
	}
	virtual void AddFailure(UnitTest* _test, BaseException* _exception) {
		FExclusiveZone zone(sync_obj);
		failures.emplace_back(new UnitTestFailure(_test, _exception));
	}
	virtual void StartTest(UnitTest* _test) {
		FExclusiveZone zone(sync_obj);
		++run_tests;
	}
	virtual void EndTest(UnitTest* _test) {
		FExclusiveZone zone(sync_obj);
	}
	/// <returns>Work test count</returns>
	virtual int RunTests() {
		FExclusiveZone zone(sync_obj);
		return run_tests;
	}
	virtual int TestErrors() {
		FExclusiveZone zone(sync_obj);
		return static_cast<int>(errors.size());
	}
	virtual int TestFailures() {
		FExclusiveZone zone(sync_obj);
		return static_cast<int>(failures.size());
	}
	virtual bool WasSuccessful() {
		FExclusiveZone zone(sync_obj);
		return failures.empty() && errors.empty();
	}
	virtual bool ShouldStop() {
		FExclusiveZone zone(sync_obj);
		return stop;
	}
	virtual void Stop() {
		FExclusiveZone zone(sync_obj);
		stop = true;
	}

	virtual std::vector<UnitTestFailure*>& Errors() {
		FExclusiveZone zone(sync_obj);
		return errors;
	}
	virtual std::vector<UnitTestFailure*>& Failures() {
		FExclusiveZone zone(sync_obj);
		return failures;
	}

protected:
	virtual void SetSyncObject(FSyncObject* _sync_obj) {
		delete sync_obj;
		sync_obj = _sync_obj;
	}

protected:
	std::vector<UnitTestFailure*> errors;
	std::vector<UnitTestFailure*> failures;
	int run_tests;
	bool stop;
	FSyncObject* sync_obj;
};