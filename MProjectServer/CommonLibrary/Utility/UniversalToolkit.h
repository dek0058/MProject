#pragma once
#include "GuardDefine.h"
#include "Globaldefine.h"

class UniversalToolkit {
	DELETE_REFERENCE_CREATOR(UniversalToolkit)
		
public:

	static std::string Digest2Hex(std::vector<byte> const& _data) {
		static byte digits[] = "0123456789abcdef";
		std::string result;
		result.reserve(_data.size() * 2);
		for (auto b : _data) {
			result.push_back(digits[b >> 4]);
			result.push_back(digits[b & 0xF]);
		}
		return result;
	}

};
