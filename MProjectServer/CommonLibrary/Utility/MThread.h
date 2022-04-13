#pragma once
#include <thread>
#include <string>
#include <memory>

class MThread {
public:
	enum class ThreadState : unsigned char {
		None,
		Running,
		Stopped
	};


public:
	MThread(std::wstring _name);
	~MThread();

	void Start();
	void Stop() { ; }
	void Resume() { ; }

	void SetPriority(int _priority);

	// getter
	ThreadState GetState() const {
		return state;
	}

protected:
	
	virtual void OnStart() { 
		state = ThreadState::Running;
	}
	virtual void OnUpdate() { ; }
	virtual void OnStop() { 
		state = ThreadState::Stopped;
	}

private:
	void OnAction();

private:
	std::unique_ptr<std::thread> thread;
	ThreadState state;
};

