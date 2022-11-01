/*****************************************************************//**
 * \file   String.h
 * \brief  String primitive object type
 *
 * \author dek0058
 * \date   2022-11-01
 *********************************************************************/

#pragma once
#include <string>
#include <locale>
#include <format>

using DefaultChar = wchar_t;
using DefaultString = std::wstring;
using DefaultStringView = std::wstring_view;

template<typename T>
concept DefaultStringType = std::is_same_v<T, DefaultChar> || std::is_same_v<T, DefaultString>;

#define pTEXT(str) L##str

struct FString {

// Constructors
	FString() = default;
	FString(char const* _str);
	FString(std::string const& _str);
	FString(std::string_view const& _str);
	FString(DefaultChar const* _str) : str(_str) {}
	FString(DefaultString const& _str) : str(_str) {}
	FString(FString const& _str) : str(_str.str) {}
	FString(FString&& _str) noexcept : str(std::move(_str.str)) {}

// Operators
	operator DefaultString() const { 
		return str; 
	}
	
	FString& operator=(DefaultChar const* _str) {
		str = _str; return *this;
	}
	FString& operator=(DefaultString const& _str) {
		str = _str; return *this; 
	}
	FString& operator=(FString const& _str) {
		str = _str.str; return *this;
	}
	FString& operator=(FString&& _str) noexcept {
		str = std::move(_str.str); return *this;
	}
	
	FString& operator+=(DefaultChar const* _str) {
		str += _str; return *this;
	}
	FString& operator+=(DefaultString const& _str) {
		str += _str; return *this;
	}
	FString& operator+=(FString const& _str) {
		str += _str.str; return *this;
	}
	FString& operator+=(FString&& _str) noexcept {
		str += std::move(_str.str); return *this;
	}

	FString operator+(DefaultChar const* _str) const {
		return FString(str + _str);
	}
	FString operator+(DefaultString const& _str) const {
		return FString(str + _str);
	}
	FString operator+(FString const& _str) const {
		return FString(str + _str.str);
	}
	FString operator+(FString&& _str) const noexcept {
		return FString(str + std::move(_str.str));
	}
	

// Methods
	std::string ToString() const;
	DefaultString Data() const {
		return str;
	}
	DefaultStringView DataView() const {
		return str;
	}

private:
// Fields
	DefaultString str;

public:
	const static constinit size_t max_size = 2'048Ui64;	// byte
};
