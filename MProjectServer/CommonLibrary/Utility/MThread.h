#pragma once
#include <thread>
#include <string>

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

protected:
	
	virtual void Run() { ; }
	virtual void Stop() { ; }

private:
	void OnAction();

private:
	std::thread thread;
	ThreadState state;
};

