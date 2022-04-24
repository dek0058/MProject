#pragma once
#include "GuardDefine.h"
#include "Globaldefine.h"

class UniversalToolkit {
	UniversalToolkit() = delete;
	UniversalToolkit(UniversalToolkit const&) = delete;
	UniversalToolkit& operator = (UniversalToolkit const&) = delete;
		
public:

	static ulong GetHashCode(std::string_view _value);
	
};
