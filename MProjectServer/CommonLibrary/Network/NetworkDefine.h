#pragma once
#include "GlobalDefine.h"


constexpr uint BUFFER_BLOCKS_PER_BUCKET = 4;
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
	ushort port;
	int thread_count;
	ESessionType session_type;
	int session_count;
	int send_buffer_size;
	int recv_buffer_size;
	int max_packet_size;
	std::wstring forwarding_ip;
	ushort forwarding_port;
	FAcceptInfo()
		: ip(L""), port(0), thread_count(0), session_type(ESessionType::Client), session_count(0),
		send_buffer_size(0), recv_buffer_size(0), max_packet_size(0),
		forwarding_ip(L""), forwarding_port(0) {}
};

struct FConnectInfo {
	std::wstring ip;
	std::wstring failover_ip;
	ushort port;
	int thread_count;
	ESessionType session_type;
	int send_buffer_size;
	int recv_buffer_size;
	int max_packet_size;
	FConnectInfo() : ip(L""), failover_ip(L""), port(0), thread_count(0), session_type(ESessionType::Client), 
		send_buffer_size(0), recv_buffer_size(0), max_packet_size(0) {}
};

