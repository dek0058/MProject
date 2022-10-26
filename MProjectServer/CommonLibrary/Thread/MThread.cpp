#include "MThread.h"


MThread::MThread() : fps(300) {
}

MThread::MThread(int _fps) : fps(_fps) {
}

MThread::~MThread() {
	Stop();
	if (state != EState::None && state != EState::Stopped) {
		if (data.joinable()) {
			data.join();
		}
	}
}

void MThread::Start(std::stop_token _stop_token) {
	if (state == EState::None || state == EState::Stopped) {
		data = std::jthread(&MThread::Thread_Run, this, _stop_token);
	}
}

void MThread::Stop() {
	if (IsRunnable() == true) {
		state = EState::Stopping;
	}
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
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		fps.Sleep();
		// do something
	}
	state = EState::Stopped;
	OnStop();
}


