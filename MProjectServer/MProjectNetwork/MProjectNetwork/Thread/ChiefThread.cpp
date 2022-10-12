#include "ChiefThread.h"
#include "EliteThread.h"
#include "MProjectLogger/Logger/SpdLogger.h"
#include "MProjectNetwork/NetworkDefine.h"

namespace mproject {
namespace network {

ChiefThread::ChiefThread(FString _name, int _fps) :
	MThread(_fps), name(_name) {
	//logger = std::make_unique<logger::SpdLogger>(name, "./Logs/");
	
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

