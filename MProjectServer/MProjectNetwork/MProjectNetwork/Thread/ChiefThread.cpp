#include "ChiefThread.h"
#include "EliteThread.h"
#include "MProjectLogger/Logger/SpdLogger.h"
#include "MProjectNetwork/NetworkDefine.h"

namespace mproject {
namespace network {

ChiefThread::ChiefThread(FString _name, int _fps) :
	MThread(_fps), name(_name), fps(_fps) {
	logger = std::make_unique<logger::SpdLogger>(name, FString(pTEXT("./Logs")));
}

ChiefThread::~ChiefThread() {
	OnStop();
	// join.......
}

void ChiefThread::OnStart() {
	for (auto& elite_thread : sub_threads) {
		if (elite_thread.get() != nullptr) {
			elite_thread->Start(stop_source.get_token());
		}
	}
}

void ChiefThread::OnUpdate() {
	// TODO

}

void ChiefThread::OnStop() {
	stop_source.request_stop();
}

void ChiefThread::AddSubThread(std::shared_ptr<EliteThread> _sub_thread) {
	sub_threads.emplace_back(_sub_thread);
}

}	// network
}	// mproject

