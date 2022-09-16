#include "FramesPerSecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

void FramesPerSecond::Update() {
	if (count == 0) {
		start_time = boost::posix_time::microsec_clock::local_time();
	}
	if (count >= GetFixed()) {
		auto cur_time = boost::posix_time::microsec_clock::local_time();
		delta_time = 1.0f / ((cur_time - start_time).ticks() / (float)GetFixed());
		count = 0;
		start_time = cur_time;
	}
	++count;
}

void FramesPerSecond::Sleep() {
	auto took_time = boost::posix_time::microsec_clock::local_time() - start_time;
	auto sleep_time = (__int64)(count * 1000.0f / GetFixed()) - took_time.ticks();
	if (sleep_time > 0) {
		boost::this_thread::sleep_for(boost::chrono::milliseconds(sleep_time));
	}
}
