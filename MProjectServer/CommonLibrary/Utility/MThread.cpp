#include "MThread.h"
#include <windows.h>

MThread::MThread(std::wstring_view _name, int _fixed) 
	: state(ThreadState::None), name(_name), fps(_fixed) { ; }

void MThread::Start() {
	if (state != ThreadState::None) {
		return;
	}
	thread = std::move(std::make_unique<std::thread>(&MThread::OnAction, this));
}

void MThread::Stop() {
	switch (state)
	{
		case MThread::ThreadState::Running:
		{
			state = ThreadState::Stopping;
		} break;
		case MThread::ThreadState::Stopping: {
			DWORD result = WaitForSingleObject(thread->native_handle(), 1000);
			if (result == WAIT_OBJECT_0) {
				state = ThreadState::Stopped;
			}
		} break;
	}
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
				fps.Update();
				OnUpdate();
			} catch (std::exception const _excetion) {
				// exception;
			}
			fps.Sleep();
		}
	}
	catch (std::exception const _excetion) {
		//std::cout << _excetion.what() << std::endl;
	} catch (...) {
		//std::cout << "Unknown exception" << std::endl;
	}
	
	OnStop();
}
