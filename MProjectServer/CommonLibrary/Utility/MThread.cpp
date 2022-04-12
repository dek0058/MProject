#include "MThread.h"

MThread::MThread(std::wstring _name) 
	: state(ThreadState::None) {
	
}

MThread::~MThread() {
	thread.join();
}

void MThread::Start() {
		
}

void MThread::OnAction() {
	
}
