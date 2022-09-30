#include "MThread.h"


MThread::MThread() /*: fps(300)*/ {
}

MThread::MThread(int _fps) /* fps(_fps)*/ {
}

MThread::~MThread() {
	Stop();
}

void MThread::Start() {
	//data = std::jthread(&MThread::Thread_Run, this);
}

void MThread::Stop() {
	if (IsRunnable() == false) {
		return;
	}
	state = EState::Stopping;
	data.request_stop();
}

void MThread::Thread_Run(std::stop_token _token) {
	auto thread_id = std::this_thread::get_id();
	std::stop_callback stop_callback(_token, [this, thread_id] {
		state = EState::Stopped;
		OnStop();
	});

	state = EState::Running;
	OnStart();
	
	while (state == EState::Running) {
		//fps.Update();
		OnUpdate();
		//fps.Sleep();
		// do something
	}
	state = EState::Stopped;
	OnStop();
}


