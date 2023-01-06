#pragma once
#include "String.h"
#include "Utility/HashUtility.h"
#include <Windows.h>
#include <WinNls.h>


FString::FString(char const* _str, unsigned int _encoding) {
	int size_needed = MultiByteToWideChar(_encoding, 0, _str, -1, NULL, 0);
	data.resize(size_needed, '\0');
	MultiByteToWideChar(_encoding, 0, _str, -1, &data[0], size_needed);
}

FString::FString(std::string const& _str, unsigned int _encoding) {
    int size_needed = MultiByteToWideChar(_encoding, 0, &_str[0], (int)_str.size(), NULL, 0);
    data.resize(size_needed, '\0');
    MultiByteToWideChar(_encoding, 0, &_str[0], (int)_str.size(), &data[0], size_needed);
}

FString::FString(std::string_view const& _str, unsigned int _encoding) {
	int size_needed = MultiByteToWideChar(_encoding, 0, &_str[0], (int)_str.size(), NULL, 0);
	data.resize(size_needed, '\0');
	MultiByteToWideChar(_encoding, 0, &_str[0], (int)_str.size(), &data[0], size_needed);
}

StringKey FString::GetKey() const {
    return HashUtility::Hash(data);
}

std::string FString::ToString(unsigned int _encoding) const {
    int slength = static_cast<int>(data.length()) + 1;
    int len = WideCharToMultiByte(_encoding, 0, data.c_str(), slength, 0, 0, 0, 0);
    std::string result(len - 1, '\0');
    WideCharToMultiByte(_encoding, 0, data.c_str(), slength, &result[0], len, 0, 0);
    return result;
}

