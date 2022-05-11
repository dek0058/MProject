#pragma once
#include <thread>
#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <boost/date_time/posix_time/ptime.hpp>
#include "FramesPerSecond.h"

class MThread {
	using ThreadDeleagte = std::vector<std::function<void()>>;
	
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
	
	void AddStartDelegate(std::function<void()> _delegate) {
		start_delegate.emplace_back(_delegate);
	}
	
	void AddStopDelegate(std::function<void()> _delegate) {
		stop_delegate.emplace_back(_delegate);
	}

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
		for (auto& callback : start_delegate) {
			callback();
		}
	}
	virtual void OnUpdate() = 0;
	virtual void OnStop() { 
		state = ThreadState::Stopped;
		for (auto& callback : stop_delegate) {
			callback();
		}
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
	ThreadDeleagte start_delegate;
	ThreadDeleagte stop_delegate;
	ThreadState state;
	std::wstring name;
};

