#pragma once
#include "GlobalDefine.h"

struct FBaseProtocol {
	
	size_t GetSize() const {
		return 0;
	}

	std::string GetName() const {
		return std::string(typeid(this).name());
	}

	
private:
	
};
