/*****************************************************************//**
 * \file   String.h
 * \brief  String primitive object type
 *
 * \author dek0058
 * \date   2022-10-11
 * \version 0.1
 *********************************************************************/

#pragma once
#include <string>
#include <locale>
#include <codecvt>

struct FString {
	
	// Constructors
	FString() = default;
	//std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(_str)
	FString(const char* _str) : str() {}
	FString(const std::string& _str) : str(_str.begin(), _str.end()) {}
	FString(const std::wstring& _str) : str(_str) {}
	FString(const FString& _str) : str(_str.str) {}
	FString(FString&& _str) noexcept : str(std::move(_str.str)) {}

	// Operators
	//str = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(_str)
	FString& operator=(const char* _str) { ; return *this; }
	FString& operator=(const std::string& _str) { str = std::wstring(_str.begin(), _str.end()); return *this; }
	FString& operator=(const std::wstring& _str) { str = _str; return *this; }
	FString& operator=(const FString& _str) { str = _str.str; return *this; }
	FString& operator=(FString&& _str) noexcept { str = std::move(_str.str); return *this; }

	// Methods
	std::string ToStdString() const { return std::string(str.begin(), str.end()); }
	std::wstring ToStdWString() const { return str; }

	// Operators
	operator std::string() const { return std::string(str.begin(), str.end()); }
	operator std::wstring() const { return str; }

private:
	// Fields
	std::wstring str;
};
