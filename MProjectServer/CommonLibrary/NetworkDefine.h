#pragma once
#include "GlobalDefine.h"


constexpr uint SESSION_CAPACITY = 16'384;
constexpr uint NET_EVENT_CAPCITY = 256;

// server variable define
using SessionKey = uint;


enum class ESessionType : byte {
	Client,
	//LoginServer,
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

enum class ENetEventType : byte {
	None,
	Accepted,
	Connected,
	Disconnected,
	Error,
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

struct FConnectInfo {
	std::wstring ip;
	std::wstring failover_ip;
	ushort port;
	int thread_count;
	ESessionType session_type;
	FConnectInfo() : ip(L""), failover_ip(L""), port(0), thread_count(0), session_type(ESessionType::Client) {}
};

