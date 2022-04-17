#pragma once
#include <boost/date_time/posix_time/ptime.hpp>

class FramesPerSecond {
public:
	FramesPerSecond(int _fixed = 10) : count(0), delta_time(0.0), fixed(_fixed) { ; }

	virtual void Update();
	virtual void Sleep();

	// getter
	double GetDeltaTime() const { 
		return delta_time; 
	}

private:
	int GetFixed() const {
		return fixed;
	}

protected:
	boost::posix_time::ptime start_time;
	int count;
	double delta_time;
	int fixed;
};
