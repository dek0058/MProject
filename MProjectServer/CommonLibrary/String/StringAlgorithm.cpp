#include "StringAlgorithm.h"

#include <cctype>
#include <cwctype>
#include <algorithm>




FString& StringAlgorithm::ToUpper(FString& _str) {
	ToUpper(_str.data); return _str;
}

FString& StringAlgorithm::ToLower(FString& _str) {
	ToLower(_str.data); return _str;
}

FString StringAlgorithm::ToUpper_Copy(FString const& _str) {
	FString result = _str; ToUpper(result.data); return std::move(result);
}

FString StringAlgorithm::ToLowerCopy(FString const& _str) {
	FString result = _str; ToLower(result.data); return std::move(result);
}

void StringAlgorithm::ToUpper(std::basic_string<char>& _str) {
	std::transform(_str.begin(), _str.end(), _str.begin(), std::toupper);
}
void StringAlgorithm::ToUpper(std::basic_string<wchar_t>& _str) {
	std::transform(_str.begin(), _str.end(), _str.begin(), std::towupper);
}

void StringAlgorithm::ToLower(std::basic_string<char>& _str) {
	std::transform(_str.begin(), _str.end(), _str.begin(), std::tolower);
}

void StringAlgorithm::ToLower(std::basic_string<wchar_t>& _str) {
	std::transform(_str.begin(), _str.end(), _str.begin(), std::towlower);
}
