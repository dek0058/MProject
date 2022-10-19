/*****************************************************************//**
 * \file   MThread.h
 * \brief  MThread class
 * 
 * \author dek0058
 * \date   2022-09-30
 * \version 0.1
 *********************************************************************/
#pragma once

#include "GlobalDefine.h"
#include "Utility/FramesPerSecond.h"


class MThread : public std::enable_shared_from_this<MThread> {
public:
	enum class EState : byte {
		None,
		Running,
		Stopping,
		Stopped,
	};
	
public:
	MThread();

	/**
	 * \param _fps Frames per second
	 */
	MThread(int _fps);

	~MThread();
	
	/**
	 * \brief Start thread
	 */
	void Start(std::stop_token _stop_token);
	
	/**
	 * \brief Stop thread
	 */
	void Stop();

	/**
	 * \brief Is thread runnable
	 * \return true if runnable
	 */
	bool IsRunnable() const {
		return state == EState::Running;
	}
	
protected:
	virtual void OnStart() {}
	virtual void OnUpdate() {}
	virtual void OnStop() {}

private:
	void Thread_Run(std::stop_token _stop_token);

private:
	std::jthread data;
	EState state = EState::None;
	FramesPerSecond fps;
};
