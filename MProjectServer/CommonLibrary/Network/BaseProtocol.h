#pragma once
#include "NetworkDefine.h"
#include "Utility/UniversalToolkit.h"

struct FBaseProtocol {
	HashCode hash_code;
	uint lenth;
	uint tag;
	
	FBaseProtocol() : lenth(0), tag(0) {
		hash_code = UniversalToolkit::GetHashCode(typeid(this).name());
	}
};
