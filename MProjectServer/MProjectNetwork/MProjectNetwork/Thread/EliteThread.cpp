#include "EliteThread.h"
#include "ChiefThread.h"

namespace mproject {
namespace network {

EliteThread::EliteThread(int _fps, std::shared_ptr<ChiefThread> _chief_thread) :
	MThread(_fps),
	chief_thread(_chief_thread) {

}

void EliteThread::OnStart() {
	
}

void EliteThread::OnUpdate() {

}

void EliteThread::OnStop() {
	
}

}	// network
}	// mproject
