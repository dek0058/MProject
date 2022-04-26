#pragma once
#include "GuardDefine.h"
#include "Globaldefine.h"

struct FPacket;

class UniversalToolkit {
	UniversalToolkit() = delete;
	UniversalToolkit(UniversalToolkit const&) = delete;
	UniversalToolkit& operator = (UniversalToolkit const&) = delete;
		
public:

	//static FPacket* SerializePacket();
	//static FPacket* DeserializePacket(byte* _data);
};
