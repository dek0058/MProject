#include "MThread.h"


MThread::MThread() /*: fps(300)*/ {
}

MThread::MThread(int _fps) /* fps(_fps)*/ {
}

MThread::~MThread() {
	Stop();
}

void MThread::Start(std::stop_token _stop_token) {
	data = std::jthread(&MThread::Thread_Run, this, _stop_token);
}

void MThread::Stop() {
	if (IsRunnable() == false) {
		return;
	}
	state = EState::Stopping;
}

void MThread::Thread_Run(std::stop_token _stop_token) {
	auto thread_id = std::this_thread::get_id();
	std::stop_callback stop_callback(_stop_token, [this, thread_id] {
		state = EState::Stopped;
		OnStop();
	});

	state = EState::Running;
	OnStart();
	
	while (state == EState::Running) {
		if (_stop_token.stop_requested()) {
			return;
		}
		fps.Update();
		OnUpdate();
		fps.Sleep();
		// do something
	}
	state = EState::Stopped;
	OnStop();
}


