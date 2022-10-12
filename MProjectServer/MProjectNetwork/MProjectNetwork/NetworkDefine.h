#pragma once

#include "GlobalDefine.h"
#include "GuardDefine.h"



namespace mproject {
namespace network {

/*
	네트워크 관련 정의
*/

using SessionKey = int;

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

constexpr uint Connect_Thread_Count = 4;

}	// network
}	// mproject