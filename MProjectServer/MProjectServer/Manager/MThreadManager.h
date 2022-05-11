#pragma once

#include "Utility/TSingleton.h"
#include "Utility/MThread.h"
#include "MProjectServerDefine.h"

class MThreadManager : public TSingleton<MThreadManager> {
protected:
	MThreadManager();

public:
	void OnStart();
	
	// getter
	std::shared_ptr<MThread>* GetThread(ThreadType _type);
	bool Stopped() const;
	

	void Stop() { ; }
	void AllStop();


private:
	std::map<ThreadType, std::shared_ptr<MThread>> threads;
};

