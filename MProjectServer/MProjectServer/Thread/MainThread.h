#pragma once
#include "Utility/MThread.h"

// inherit thread class...
class MainThread final : public MThread {
	
public:
	MainThread();
	~MainThread();

protected:

	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnStop() override;

};
