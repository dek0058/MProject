#pragma once
#include <string>

class HashUtility {
	HashUtility(HashUtility const&) = delete;
	HashUtility& operator = (HashUtility const&) = delete;

public:

	[[nodiscard]] static size_t Hash(std::string const& str);
	
	[[nodiscard]] static size_t Hash(std::wstring const& str);

};
