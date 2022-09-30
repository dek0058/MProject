#include "ChiefThread.h"
#include "EliteThread.h"

namespace mproject {
namespace network {

ChiefThread::ChiefThread(int _fps, size_t _sub_thread_count) :
	MThread(_fps) {
	
	sub_threads.reserve(_sub_thread_count);
	for (size_t i = 0; i < sub_threads.size(); ++i) {
		sub_threads.emplace_back(std::make_shared<EliteThread>(_fps, std::static_pointer_cast<ChiefThread>(shared_from_this())));
	}
	
}

void ChiefThread::OnStart() {
	for (auto& elite_thread : sub_threads) {
		if (elite_thread.get() != nullptr) {
			elite_thread->Stop();
		}
	}
	sub_threads.clear();
}

void ChiefThread::OnUpdate() {
	// TODO

}

void ChiefThread::OnStop() {

}

}	// network
}	// mproject