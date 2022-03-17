#pragma once
#include "GlobalDefine.h"


// server variable define
using SessionKey = uint;


enum class ESessionType : byte {
	Client,
	LoginServer,
	//GameWorldServer,
	GameServer,
};


enum class ESequenceType : byte {
	Accepting,			// 응답 요청
	Connecting,			// 연결 요청
	Connected,			// 연결 중
	Disconnecting,		// 연결 종료 요청
	Disconnected,		// 연결 끊김
};


struct FAcceptInfo {
	std::wstring ip;
	ushort port_number;
	int thread_count;
	ESessionType session_type;
	int session_count;
	std::wstring forwarding_ip;
	ushort forwarding_port_number;
	FAcceptInfo()
		: ip(L""), port_number(0), thread_count(0), session_type(ESessionType::Client), session_count(0), 
		forwarding_ip(L""), forwarding_port_number(0) {}
};
