#pragma once
#include <thread>
#include <string>

class MThread {

public:
	MThread(std::wstring _name);
	~MThread();

protected:
	
	virtual bool Start() { return false; }
	virtual void Run() { ; }
	virtual void Quit() { ; }

private:
	std::thread thread;
	
};

