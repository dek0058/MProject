#include "CircularBufferTest.h"
#include "UnitTestSuite.h"
#include "UnitTestCaller.h"

#include <iostream>
#include <format>
#include <thread>

constexpr size_t capacity = 1024;
constexpr size_t message_size = 100;
constexpr size_t message_count = 100;

std::unique_ptr<CircularBuffer_M> CircularBufferTest::circular_buffer;
//std::unique_ptr<Soft_Ring_Buffer> CircularBufferTest::circular_buffer;

CircularBufferTest::CircularBufferTest(std::string const& _name) : UnitTestCase(_name) { ; }

CircularBufferTest::~CircularBufferTest()
{
}

void CircularBufferTest::Test() {
	constexpr size_t buffer_capacity = 1024;
	
	const size_t message_size = ::message_size;
	const size_t message_count = 10;

	CircularBuffer_M buffer(buffer_capacity);
	std::unique_ptr<uint8_t[]> message_buffer(new uint8_t[message_size]);
	
	std::cout << "\n";

	for (size_t i = 0; i < message_count; ++i) {
		*(size_t*)message_buffer.get() = i;
		buffer.Put(message_buffer.get(), message_size);
	}

	size_t post_size = buffer.UsedSize();
	std::cout << "capacity : " << buffer.Capacity() << std::endl;
	std::cout << "used size : " << buffer.UsedSize() << std::endl;
	std::cout << "free size : " << buffer.FreeSize() << std::endl;

	buffer.Discard(post_size);
	std::cout << "Discard buffer... \n";

	std::cout << "capacity : " << buffer.Capacity() << std::endl;
	std::cout << "used size : " << buffer.UsedSize() << std::endl;
	std::cout << "free size : " << buffer.FreeSize() << std::endl;

}

void CircularBufferTest::TestCircularBufferTest() {

	size_t times = 1;
	for (size_t i = 0; i < times; ++i) {
		std::cout << "TestCircularBufferTest " << i << std::endl;
		CircularBufferTest::circular_buffer.reset(new CircularBuffer_M(capacity));
		//CircularBufferTest::circular_buffer.reset(new Soft_Ring_Buffer(capacity));
		std::thread thread1([]() {
			const size_t message_size = ::message_size;
			const size_t message_count = ::message_count;
			
			CircularBuffer_M& buffer = *CircularBufferTest::circular_buffer;
			//Soft_Ring_Buffer& buffer = *CircularBufferTest::circular_buffer;
			std::unique_ptr<uint8_t[]> message_buffer(new uint8_t[message_size]);

			std::cout << "begin send\n";
			for (size_t i = 0; i < message_count; ++i) {
				*(size_t*)message_buffer.get() = i;
				size_t old_capacity = buffer.Capacity();
				buffer.Put(message_buffer.get(), message_size);
				size_t new_capacity = buffer.Capacity();
				if (old_capacity != new_capacity) {
					std::cout << "capacity changed from " << old_capacity << " to " << new_capacity << "\n";
				}
			}
			std::cout << "send " << message_count << std::endl;
			std::cout << "capacity : " << buffer.Capacity() << std::endl;

		});
		std::thread thread2([]() {
			const size_t message_size = ::message_size;
			const size_t message_count = ::message_count;

			CircularBuffer_M& buffer = *CircularBufferTest::circular_buffer;
			//Soft_Ring_Buffer& buffer = *CircularBufferTest::circular_buffer;
			std::unique_ptr<uint8_t[]> message_buffer(new uint8_t[message_size]);

			std::cout << "begin receive\n";
			for (size_t i = 0; i < message_count;) {
				if (!buffer.Get(message_buffer.get(), message_size)) {
					std::cout << std::format("message not arrived yet ({})... \n", i);
				} else {
					size_t msg = *(size_t*)message_buffer.get();
					if (msg != i) {
						std::cout << std::format("message {} != expected {}\n", msg, i);
						std::terminate();
						//TAssert(false);
					}
					++i;
				}
			}
			std::cout << "receive " << message_count << std::endl;
		});

		thread1.join();
		thread2.join();
	}
}

void CircularBufferTest::CircularBufferTestBenchmark()
{
}

UnitTest* CircularBufferTest::Suite()
{
	UnitTestSuite* suite = new UnitTestSuite("CircularBufferTest");
	TUnitTest_AddTest(suite, CircularBufferTest, Test);
	TUnitTest_AddTest(suite, CircularBufferTest, TestCircularBufferTest);
	//TUnitTest_AddTest(suite, SPSCQueueTest, SPSCQueueBenchmark);
	return suite;
}
