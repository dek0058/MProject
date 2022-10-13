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
	FString(const char* _str, std::locale locale = std::locale()) {
		std::mbstate_t state {0};
		wchar_t* from_next = str.data();
		
		/*std::codecvt<wchar_t, char, std::mbstate_t> codecvt();
		std::codecvt<wchar_t, char, std::mbstate_t>(locale).in(
			state,
			_str,
			_str + strlen(_str),
			_str,
			&str[0],
			&str[0] + str.max_size(),
			from_next
		);*/
		std::string temp(_str);
		str.assign(temp.begin(), temp.end());
	}
	FString(const std::string& _str) : str(_str.begin(), _str.end()) {}
	FString(const std::wstring& _str) : str(_str) {}
	FString(const FString& _str) : str(_str.str) {}
	FString(FString&& _str) noexcept : str(std::move(_str.str)) {}

	// Operators
	FString& operator=(const char* _str) { ; return *this; }
	FString& operator=(const std::string& _str) { str.assign(_str.begin(), _str.end()); return *this; }
	FString& operator=(const std::wstring& _str) { str = _str; return *this; }
	FString& operator=(const FString& _str) { str = _str.str; return *this; }
	FString& operator=(FString&& _str) noexcept { str = std::move(_str.str); return *this; }

	// Methods
	/*std::string ToString() { 
		std::wstring_convert<std::codecvt_utf8<wchar_t>> conv1;
		return conv1.to_bytes(str);
	}*/

	// Operators
	operator std::wstring() const { return str; }

private:
	// Fields
	std::wstring str;
};

