#include "FramePerSecondTest.h"
#include "UnitTestSuite.h"
#include "UnitTestCaller.h"

#include "Utility/MThread.h"

#include <string>
#include <boost/thread/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/date_time.hpp>


class TestThread final : public MThread {
public:
	TestThread() : MThread(L"TestThread", 60) { ; }

protected:

	virtual void OnStart() override {
		MThread::OnStart();
	}
	virtual void OnUpdate() {
		std::cout << "Fps-" << fps.GetDeltaTime() << std::endl;
	}
	virtual void OnStop() override {
		MThread::OnStop();
	}
};

FramePerSecondTest::FramePerSecondTest(std::string const& _name) : UnitTestCase(_name) { ; }

FramePerSecondTest::~FramePerSecondTest() { ; }

void FramePerSecondTest::TestFramePerSecond() {
	TestThread thread;
	thread.Start();
	std::this_thread::sleep_for(std::chrono::seconds(10));
	thread.Stop();
}

UnitTest* FramePerSecondTest::Suite() {
	UnitTestSuite* suite = new UnitTestSuite("FramePerSecondTest");
	TUnitTest_AddTest(suite, FramePerSecondTest, TestFramePerSecond);
	return suite;
}
