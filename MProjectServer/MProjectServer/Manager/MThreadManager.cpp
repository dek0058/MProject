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
	threads.emplace(ThreadType::Main, main_thread);

	for (auto& thread : threads) {
		thread.second->Start();
	}
}

std::shared_ptr<MThread>* MThreadManager::GetThread(ThreadType _type) {
	auto result = threads.find(_type);
	return result != threads.end() ? &result->second : nullptr;
}

bool MThreadManager::Stopped() const
{
	for (auto& thread : threads)
	{
		if (thread.second->GetState() == MThread::ThreadState::Running || thread.second->GetState() == MThread::ThreadState::Stopping)
		{
			return false;
		}
	}
	return true;
}

void MThreadManager::AllStop()
{
	for (auto& thread : threads)
	{
		thread.second->Stop();
	}
	threads.clear();
}