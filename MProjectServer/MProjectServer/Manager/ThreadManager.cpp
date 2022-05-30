#include "ThreadManager.h"

#include "Thread/MainThread.h"
#include "Core/LogManager.h"

ThreadManager::ThreadManager() {
}

void ThreadManager::OnStart() {
	if (false == Stopped())
	{
		LogManager::GetMutableInstance().GenericLog(ELogLevel::Critical, "MThreadManager", "OnStart", "ThreadManager is already running");
		return;
	}
	
	std::shared_ptr<MainThread> main_thread(new MainThread);
	AddThread(main_thread, main_thread->GetThreadType());
	

	for (auto& data : threads) {
		auto& [thread, completed] = data.second;
		thread->Start();
	}
}

void ThreadManager::AllStop()
{
	for (auto& data : threads) {
		auto& [thread, completed] = data.second;
		thread->Stop();
	}
	threads.clear();
}

//! Getter

std::shared_ptr<MThread>* ThreadManager::GetThread(ThreadType _type) {
	auto result = threads.find(_type);
	return result != threads.end() ? &std::get<std::shared_ptr<MThread>>(result->second) : nullptr;
}

bool ThreadManager::Stopped() const
{
	for (auto& data : threads)
	{
		auto& [thread, completed] = data.second;
		if (thread->GetState() == MThread::ThreadState::Running || thread->GetState() == MThread::ThreadState::Stopping)
		{
			return false;
		}
	}
	return true;
}


void ThreadManager::AddThread(std::shared_ptr<MThread> const& _thread, ThreadType _type) {
	threads.emplace(_type, std::make_tuple(_thread, false));
	_thread->AddStartDelegate([this, _type]() { OnCompleted(_type); });
}


void ThreadManager::OnCompleted(ThreadType _type) {
	std::get<bool>(threads[_type]) = true;
	bool all_completed = true;
	for (auto& data : threads) {
		if (false == std::get<bool>(data.second)) {
			all_completed = false;
			break;
		}
	}
	if (false == all_completed) {
		return;
	}
	for (auto& callback : completed_delegate) {
		callback();
	}
}
