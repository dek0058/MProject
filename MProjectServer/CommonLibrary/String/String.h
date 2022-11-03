/*****************************************************************//**
 * \file   String.h
 * \brief  String primitive object type
 *
 * \author dek0058
 * \date   2022-11-03
 *********************************************************************/

#pragma once
#include <string>

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
	FString(DefaultChar const* _str) : data(_str) {}
	FString(DefaultString const& _str) : data(_str) {}
	FString(FString const& _str) : data(_str.data) {}
	FString(FString&& _str) noexcept : data(std::move(_str.data)) {}

// Operators
	operator DefaultString() const { 
		return data; 
	}
	
	FString& operator=(DefaultChar const* _str) {
		data = _str; return *this;
	}
	FString& operator=(DefaultString const& _str) {
		data = _str; return *this; 
	}
	FString& operator=(FString const& _str) {
		data = _str.data; return *this;
	}
	FString& operator=(FString&& _str) noexcept {
		data = std::move(_str.data); return *this;
	}
	
	FString& operator+=(DefaultChar const* _str) {
		data += _str; return *this;
	}
	FString& operator+=(DefaultString const& _str) {
		data += _str; return *this;
	}
	FString& operator+=(FString const& _str) {
		data += _str.data; return *this;
	}
	FString& operator+=(FString&& _str) noexcept {
		data += std::move(_str.data); return *this;
	}

	FString operator+(DefaultChar const* _str) const {
		return FString(data + _str);
	}
	FString operator+(DefaultString const& _str) const {
		return FString(data + _str);
	}
	FString operator+(FString const& _str) const {
		return FString(data + _str.data);
	}
	FString operator+(FString&& _str) const noexcept {
		return FString(data + std::move(_str.data));
	}
	

// Methods
	std::string ToString() const;

public:
// Fields
	DefaultString data;

public:
	const static constinit size_t max_size = 2'048Ui64;	// byte
};
