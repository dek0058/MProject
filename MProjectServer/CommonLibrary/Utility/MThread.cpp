#include "MThread.h"
#include <windows.h>

MThread::MThread(std::wstring _name) 
	: state(ThreadState::None) {
	
}

MThread::~MThread() {
	thread->join();
}

void MThread::Start() {
	if (state != ThreadState::None) {
		return;
	}
	thread = std::move(std::make_unique<std::thread>(&MThread::OnAction, this));
}

void MThread::SetPriority(int _priority) {
	if (state == ThreadState::None) {
		return;
	}
	SetThreadPriority(thread->native_handle(), _priority);
}

void MThread::OnAction() {
	try {
		OnStart();
		if(GetState() != ThreadState::Running) {
			throw; // 예외처리 필요
		}
		while (GetState() == ThreadState::Running) {
			try {
				OnUpdate();
			} catch (std::exception const _excetion) {
				// exception;
			}
			
			
		}
	}
	catch (std::exception const _excetion) {
		//std::cout << _excetion.what() << std::endl;
	} catch (...) {
		//std::cout << "Unknown exception" << std::endl;
	}
	
	OnStop();
}
