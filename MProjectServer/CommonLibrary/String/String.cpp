#pragma once
#include "String.h"
#include <Windows.h>
#include <WinNls.h>


FString::FString(char const* _str) {
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, _str, -1, NULL, 0);
	str.resize(size_needed, '\0');
	MultiByteToWideChar(CP_UTF8, 0, _str, -1, &str[0], size_needed);
}

FString::FString(std::string const& _str) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &_str[0], (int)_str.size(), NULL, 0);
    str.resize(size_needed, '\0');
    MultiByteToWideChar(CP_UTF8, 0, &_str[0], (int)_str.size(), &str[0], size_needed);
}

FString::FString(std::string_view const& _str) {
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &_str[0], (int)_str.size(), NULL, 0);
	str.resize(size_needed, '\0');
	MultiByteToWideChar(CP_UTF8, 0, &_str[0], (int)_str.size(), &str[0], size_needed);
}

std::string FString::ToString() const {
    int slength = static_cast<int>(str.length()) + 1;
    int len = WideCharToMultiByte(CP_ACP, 0, str.c_str(), slength, 0, 0, 0, 0);
    std::string result(len - 1, '\0');
    WideCharToMultiByte(CP_ACP, 0, str.c_str(), slength, &result[0], len, 0, 0);
    return result;
}
