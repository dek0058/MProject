#include "MThread.h"


MThread::MThread() /*: fps(300)*/ {
}

MThread::MThread(int _fps) /* fps(_fps)*/ {
}

MThread::~MThread() {
	Stop();
}

void MThread::Start() {
	data = std::jthread(&MThread::Thread_Run, shared_from_this());
}

void MThread::Stop() {
	if (IsRunnable() == false) {
		return;
	}
	state = EState::Stopping;
	data.request_stop();
}

void MThread::Thread_Run() {
	std::stop_source stop_source;
	std::stop_token stop_token = stop_source.get_token();
	
	auto thread_id = std::this_thread::get_id();
	std::stop_callback stop_callback(stop_token, [this, thread_id] {
		state = EState::Stopped;
		OnStop();
	});

	state = EState::Running;
	OnStart();
	
	while (state == EState::Running) {
		fps.Update();
		OnUpdate();
		fps.Sleep();
		// do something
	}
	state = EState::Stopped;
	OnStop();
}


