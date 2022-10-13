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
	FString(const std::u8string& _str) : str(_str) {}
	FString(const FString& _str) : str(_str.str) {}
	FString(FString&& _str) noexcept : str(std::move(_str.str)) {}

	// Operators
	FString& operator=(const std::u8string& _str) { str = _str; return *this; }
	FString& operator=(const FString& _str) { str = _str.str; return *this; }
	FString& operator=(FString&& _str) noexcept { str = std::move(_str.str); return *this; }

	// Methods

	// Operators
	operator std::u8string() const { return str; }

private:
	// Fields
	std::u8string str;
};

