#include "EliteThread.h"
#include "ChiefThread.h"

namespace mproject {
namespace network {

EliteThread::EliteThread(int _fps, std::weak_ptr<ChiefThread> _chief_thread) :
	MThread(_fps),
	chief_thread(_chief_thread) {

}

}	// network
}	// mproject
