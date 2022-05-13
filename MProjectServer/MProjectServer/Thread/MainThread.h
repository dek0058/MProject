#pragma once
#include "Utility/MThread.h"
#include "MProjectServerDefine.h"

// inherit thread class...
class MainThread final : public MThread, IThread {
	
public:
	MainThread();
	~MainThread();

	//! Getter
	ThreadType GetThreadType() const {
		return ThreadType::Main;
	}
	
protected:

	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnStop() override;

};
