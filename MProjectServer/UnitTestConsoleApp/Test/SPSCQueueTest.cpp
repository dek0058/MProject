#include "SPSCQueueTest.h"
#include "UnitTestSuite.h"
#include "UnitTestCaller.h"

#include <ranges>
#include <iostream>
#include <format>
#include <time.h>

SPSCQueueTest::SPSCQueueTest(std::string const& _name) : UnitTestCase(_name) { ; }
SPSCQueueTest::~SPSCQueueTest() { ; }

void SPSCQueueTest::TestSPSCQueue() {
	{
		SPSCQueue<int> int_queue(1024);

		for (int i = 0; i < 100; ++i) {
			TAssert_True(int_queue.try_emplace(i * i));
		}

		while (false == int_queue.empty()) {
			if (nullptr == int_queue.front()) {
				int_queue.pop();
				continue;
			}
			int& temp = *int_queue.front();
			int_queue.pop();
		}
		std::cout << std::format("int_queue size-{}, space-{} (try_emplace)", int_queue.size(), int_queue.capacity());
	}

	{
		SPSCQueue<int> int_queue(1024);

		for (int i = 0; i < 100; ++i) {
			int_queue.emplace(i * i);
		}

		while (false == int_queue.empty()) {
			if (nullptr == int_queue.front()) {
				int_queue.pop();
				continue;
			}
			int& temp = *int_queue.front();
			int_queue.pop();
		}
		std::cout << std::format("\t int_queue size-{}, space-{} (emplace)", int_queue.size(), int_queue.capacity()) << std::endl;
	}
}

void SPSCQueueTest::SPSCQueueBenchmark() {
	constexpr int Max = 16'777'216;
	{
		SPSCQueue<int> int_queue(Max);

		for (int i = 0; i < Max - 1; ++i) {
			bool success = int_queue.try_emplace(i * i);
			TAssert_Equal(success, true);
		}

		clock_t start = clock();
		while (false == int_queue.empty()) {
			if (nullptr == int_queue.front()) {
				int_queue.pop();
				continue;
			}
			int& temp = *int_queue.front();
			int_queue.pop();
		}
		clock_t end = clock();
		double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
		std::cout << std::format("int_queue size-{}, space-{} time-{} (try_emplace)", int_queue.size(), int_queue.capacity(), time);
	}

	{
		SPSCQueue<int> int_queue(Max);

		for (int i = 0; i < Max - 1; ++i) {
			int_queue.emplace(i * i);
		}

		clock_t start = clock();
		while (false == int_queue.empty()) {
			if (nullptr == int_queue.front()) {
				int_queue.pop();
				continue;
			}
			int& temp = *int_queue.front();
			int_queue.pop();
		}
		clock_t end = clock();
		double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
		std::cout << std::format("\t int_queue size-{}, space-{} time-{} (emplace)", int_queue.size(), int_queue.capacity(), time) << std::endl;
	}
}

UnitTest* SPSCQueueTest::Suite() {
	UnitTestSuite* suite = new UnitTestSuite("SPSCQueueTest");
	TUnitTest_AddTest(suite, SPSCQueueTest, TestSPSCQueue);
	//TUnitTest_AddTest(suite, SPSCQueueTest, SPSCQueueBenchmark);
	return suite;
}
