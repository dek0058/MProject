#pragma once
#include "NetworkDefine.h"

class IOService;
struct FSession;

// required memory pool
struct FNetEvent {
	ENetEventType net_event_type;
	std::shared_ptr<IOService> IO_service;
	std::shared_ptr<FSession> session;

	FNetEvent(ENetEventType _net_event_type, std::shared_ptr<IOService> _IO_service, std::shared_ptr<FSession> _session)
		:net_event_type(_net_event_type), IO_service(_IO_service), session(_session) { ; }
};
