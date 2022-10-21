/*****************************************************************//**
 * \file   String.h
 * \brief  String primitive object type
 *
 * \author dek0058
 * \date   2022-10-14
 * \version 0.2
 *********************************************************************/

#pragma once
#include <string>
#include <locale>

namespace {
using DefaultString = std::wstring;
}

#define pTEXT(str) L##str

struct FString {
	// Constructors
	FString() = default;
	FString(std::string const& _str);
	FString(DefaultString const& _str) : str(_str) {}
	FString(FString const& _str) : str(_str.str) {}
	FString(FString&& _str) noexcept : str(std::move(_str.str)) {}

	// Operators
	FString& operator=(DefaultString const& _str) {
		str = _str; return *this; 
	}
	FString& operator=(FString const& _str) {
		str = _str.str; return *this;
	}
	FString& operator=(FString&& _str) noexcept {
		str = std::move(_str.str); return *this;
	}

	// Methods
	std::string ToString() const;
	DefaultString Data() const {
		return str;
	}
	
	// Operators
	operator DefaultString() const { 
		return str;
	}

private:
	// Fields
	DefaultString str;

public:
	const static constinit size_t max_size = 2'048Ui64;	// byte
};
