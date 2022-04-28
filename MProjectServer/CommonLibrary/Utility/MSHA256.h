#pragma once
#include "GuardDefine.h"
#include "openssl/sha.h"
#include <vector>
#include <string>

class MSHA256 {
	DELETE_REFERENCE_CREATOR(MSHA256)
public:
	MSHA256();

	void Reset();
	void Update(void const* _data, size_t _length);
	std::vector<unsigned char> Digest();

	static std::vector<unsigned char> GenerateHashcode(std::string_view _value);

private:
	SHA256_CTX context;
};
