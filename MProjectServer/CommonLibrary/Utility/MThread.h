#pragma once
#include <thread>
#include <string>
#include <memory>
#include <boost/date_time/posix_time/ptime.hpp>
#include "FramesPerSecond.h"

class MThread {
public:
	enum class ThreadState : unsigned char {
		None,
		Running,
		Stopping,
		Stopped
	};

public:
	MThread(std::wstring_view _name, int _fixed = 10);
	virtual ~MThread() { 
		GetThread()->join();
	}

	void Start();
	void Stop();

	void SetPriority(int _priority);

	// getter
	ThreadState GetState() const {
		return state;
	}

	std::wstring_view GetName() const {
		return name;
	}

protected:
	
	virtual void OnStart() { 
		state = ThreadState::Running;
	}
	virtual void OnUpdate() = 0;
	virtual void OnStop() { 
		state = ThreadState::Stopped;
	}

	// getter
	std::unique_ptr<std::thread>& GetThread() {
		return thread;
	}

private:
	void OnAction();

protected:
	FramesPerSecond fps;

private:
	std::unique_ptr<std::thread> thread;
	ThreadState state;
	std::wstring name;
};

