#include "MThread.h"


MThread::MThread() : fps(300) {
}

MThread::MThread(int _fps) : fps(_fps) {
}

MThread::~MThread() {
	Stop();
	if (data)
	{
		if (data->joinable()) {
			Join();
		}
		data.reset();
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
		Stop();
	});

	state = EState::Running;
	OnPreStart();
	OnStart();
	OnPostStart();
	
	while (state == EState::Running) {
		if (_stop_token.stop_requested()) {
			break;
		}
		fps.Update();
		OnUpdate();
		fps.Sleep();
	}
	state = EState::Stopped;
	OnStop();
}


