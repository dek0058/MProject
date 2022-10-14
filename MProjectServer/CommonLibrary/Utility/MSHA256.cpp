#include "MSHA256.h"
#include "Exception/BaseException.h"

#include <cstdlib>
#include <iomanip>
#include <sstream>

namespace {
	std::vector<unsigned char> SHA256MarkleTree(std::string_view _value, size_t _block_size) {
		std::vector<std::vector<unsigned char>> hash;
		std::vector<char> buffer(_block_size);
		MSHA256 md;

		std::copy(_value.begin(), _value.end(), buffer.begin());
		md.Reset();
		md.Update(buffer.data(), buffer.size());
		hash.emplace_back(md.Digest());

		if (true == hash.empty()) {
			return {};
		}
		size_t length = hash.size();
		while (length > 1) {
			size_t j = 0;
			for (size_t i = 0; i < length; i += 2, ++j) {
				auto& digest1 = hash[i];
				auto& digest_out = hash[j];
				if (i + 1 < length) {
					auto& digest2 = hash[i + 1];
					md.Reset();
					md.Update(digest1.data(), digest1.size());
					md.Update(digest2.data(), digest2.size());
					digest_out = md.Digest();
				}
				else {
					digest_out = digest1;
				}
			}
			length = j;
		}
		return hash[0];
	}
}

MSHA256::MSHA256() {
	Reset();
}

void MSHA256::Reset() {
	if (SHA256_Init(&context) == 0) {
		throw BaseException(FString(pTEXT("SHA256_Init failed")), __LINE__, FString(pTEXT("MSHA256.cpp")));
	}
}

void MSHA256::Update(void const* _data, size_t _length) {
	if (SHA256_Update(&context, _data, _length) == 0) {
		throw BaseException(FString(pTEXT("SHA256_Init failed")), __LINE__, FString(pTEXT("MSHA256.cpp")));
	}
}

std::vector<unsigned char> MSHA256::Digest() {
	std::vector<unsigned char> result(SHA256_DIGEST_LENGTH);
	if (SHA256_Final(result.data(), &context) == 0) {
		throw BaseException(FString(pTEXT("SHA256_Init failed")), __LINE__, FString(pTEXT("MSHA256.cpp")));
	}
	return result;
	return {};
}

// static
std::vector<unsigned char> MSHA256::GenerateHashcode(std::string_view _value) {
	return std::move(SHA256MarkleTree(_value, 1024));

}
