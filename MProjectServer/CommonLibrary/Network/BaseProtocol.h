#pragma once
#include "NetworkDefine.h"
#include "Utility/SHA256.h"

struct FBaseProtocol {
	HashCode hash_code;
	uint lenth;
	uint tag;
	
	FBaseProtocol() : lenth(0), tag(0) {
		MSHA256::GenerateHashcode(typeid(this).name());
		//hash_code = UniversalToolkit::GetHashCode(typeid(this).name());
	}
};
