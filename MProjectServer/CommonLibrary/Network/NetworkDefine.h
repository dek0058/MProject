#pragma once
#include "GlobalDefine.h"
#include "GuardDefine.h"

// server variable define
using SessionKey = uint;

constexpr uint BUFFER_BLOCKS_PER_BUCKET = 4;
constexpr uint SESSION_CAPACITY = 16'384;
constexpr uint NET_EVENT_CAPCITY = 256;
constexpr uint PACKET_MEMORY_POOL_SIZE = 65'536;

constexpr size_t PACKET_MAX_SIZE = 1'024;
constexpr size_t PACKET_BUFFER_BUILDER_SIZE = 1'024;

constexpr uint PACKET_TAG_SIZE = sizeof(uint);
constexpr uint PACKET_LEGNTH_SIZE = sizeof(uint);
constexpr uint PACKET_HASH_CODE_SIZE = sizeof(byte) * 32;
constexpr uint PACKET_HEADER_SIZE = PACKET_TAG_SIZE + PACKET_LEGNTH_SIZE + PACKET_HASH_CODE_SIZE;


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
	
	FAcceptInfo(std::wstring_view _ip, ushort _port, int _thread_count, ESessionType _session_type, int _session_count,
		int _send_buffer_size, int _recv_buffer_size, int _max_packet_size, std::wstring_view _forwarding_ip = L"", ushort _forwarding_port = 0)
		: VAR_INIT(ip), VAR_INIT(port), VAR_INIT(thread_count), VAR_INIT(session_type), VAR_INIT(session_count),
		VAR_INIT(send_buffer_size), VAR_INIT(recv_buffer_size), VAR_INIT(max_packet_size),
		VAR_INIT(forwarding_ip), VAR_INIT(forwarding_port) {}
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

	FConnectInfo(std::wstring_view _ip, ushort _port, int _thread_count, ESessionType _session_type,
		int _send_buffer_size, int _recv_buffer_size, int _max_packet_size, std::wstring_view _failover_ip = L"")
		: VAR_INIT(ip), VAR_INIT(failover_ip), VAR_INIT(port), VAR_INIT(thread_count), VAR_INIT(session_type),
		VAR_INIT(send_buffer_size), VAR_INIT(recv_buffer_size), VAR_INIT(max_packet_size) {}
};

