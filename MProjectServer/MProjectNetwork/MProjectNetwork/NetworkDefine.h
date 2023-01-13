#pragma once

#include "GlobalDefine.h"
#include "GuardDefine.h"

#include <boost/asio.hpp>
#include <concurrent_queue.h>

namespace mproject {
namespace network {

/*
	네트워크 관련 정의
*/

using UDP = boost::asio::ip::udp;
using EndPoint = UDP::endpoint;


using SessionKey = uint;

enum class ESessionType : byte {
	Test = 0,

};

enum class ESequenceType : byte {
	Accepting,			// 응답 요청
	Connecting,			// 연결 요청
	Connected,			// 연결 중
	Disconnecting,		// 연결 종료 요청
	Disconnected,		// 연결 끊김
};

/*
	개발전용 고정 값
*/

/** 연결 스레드 개수 */
constexpr uint Connect_Thread_Count = 4U;

/* 미정의 기본 고정 상수 정의 ~ */
constexpr ushort Default_Acceptor_Port = 7778U;


}	// network
}	// mproject