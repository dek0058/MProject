#pragma once

#include "Utility/TSingleton.h"
#include "Utility/MThread.h"
#include "MProjectServerDefine.h"

class MThreadManager : public TSingleton<MThreadManager> {
	using ManagerDeleagte = std::vector<std::function<void()>>;

protected:
	MThreadManager();

public:
	void OnStart();
	void Stop() { ; }
	void AllStop();

	void AddCompleteDelegate(std::function<void()> _delegate) {
		completed_delegate.emplace_back(_delegate);
	}

	//! Getter
	
	std::shared_ptr<MThread>* GetThread(ThreadType _type);
	bool Stopped() const;

private:
	void AddThread(std::shared_ptr<MThread> const& _thread, ThreadType _type);


	//! Event
	void OnCompleted(ThreadType _type);
	

private:
	std::map<ThreadType, std::tuple<std::shared_ptr<MThread>, bool>> threads;
	ManagerDeleagte completed_delegate;
};

