#include "MThreadManager.h"

#include "Thread/MainThread.h"
#include "Core/MLogger.h"

MThreadManager::MThreadManager() {
}

void MThreadManager::OnStart() {
	if (false == Stopped())
	{
		MLogger::GetMutableInstance().LogError("Thread is still running");
		return;
	}
	
	std::shared_ptr<MainThread> main_thread(new MainThread);
	threads.emplace(ThreadType::Main, std::make_tuple(main_thread, false));
	main_thread->AddStartDelegate([]() {
		//MThreadManager::GetMutableInstance().
	});

	for (auto& data : threads) {
		auto& [thread, completed] = data.second;
		thread->Start();
	}
}

std::shared_ptr<MThread>* MThreadManager::GetThread(ThreadType _type) {
	auto result = threads.find(_type);
	return result != threads.end() ? &std::get<0>(result->second) : nullptr;
}

bool MThreadManager::Stopped() const
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

void MThreadManager::AllStop()
{
	for (auto& data : threads) {
		auto& [thread, completed] = data.second;
		thread->Stop();
	}
	threads.clear();
}