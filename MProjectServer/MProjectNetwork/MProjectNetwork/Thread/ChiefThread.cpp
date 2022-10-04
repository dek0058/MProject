#include "ChiefThread.h"
#include "EliteThread.h"

namespace mproject {
namespace network {

ChiefThread::ChiefThread(int _fps) :
	MThread(_fps) {
}

ChiefThread::~ChiefThread() {
	OnStop();
	sub_threads.clear();
}

void ChiefThread::OnStart() {
	for (auto& elite_thread : sub_threads) {
		if (elite_thread.get() != nullptr) {
			elite_thread->Start();
		}
	}
}

void ChiefThread::OnUpdate() {
	// TODO

}

void ChiefThread::OnStop() {
	for (auto& elite_thread : sub_threads) {
		if (elite_thread.get() != nullptr) {
			elite_thread->Stop();
		}
	}
}

void ChiefThread::AddSubThread(std::shared_ptr<EliteThread> _sub_thread) {
	sub_threads.emplace_back(_sub_thread);
}

}	// network
}	// mproject

