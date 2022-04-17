#include "MThreadManager.h"

#include "Thread/MainThread.h"

MThreadManager::MThreadManager() {
	
}

void MThreadManager::OnStart() {
	std::shared_ptr<MainThread> main_thread(new MainThread);
	threads.emplace(ThreadType::Main, main_thread);


	for(auto& thread : threads) {
		thread.second->Start();
	}
}

std::shared_ptr<MThread>* MThreadManager::GetThread(ThreadType _type) {
	auto result = threads.find(_type);
	return result != threads.end() ? &result->second : nullptr;
}
