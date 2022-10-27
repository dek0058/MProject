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
#include <format>

using DefaultChar = wchar_t;
using DefaultString = std::wstring;

using Default_Fmt_it = std::back_insert_iterator<std::_Fmt_buffer<DefaultChar>>;
using Default_Context = std::basic_format_context<Default_Fmt_it, DefaultChar>;
using Default_Args = std::basic_format_args<Default_Context>;

#define pTEXT(str) L##str

struct FString {
	// Static
	template<typename... Types>
	_NODISCARD static std::_Format_arg_store<Default_Context, Types...> MakeFormatArgs(Types&&... _values) {
		return std::make_format_args<Default_Context>(std::forward<Types>(_values)...);
	}
	
	template<typename... Types>
	_NODISCARD static DefaultString Format(DefaultChar const* _format, Types&&... _values) {
		return FString(std::vformat(_format, MakeFormatArgs<Types>(_values)...));
	}
	
	template<typename... Types>
	_NODISCARD static DefaultString Format(DefaultString const& _format, Types&&... _values) {
		return FString(std::vformat(_format, MakeFormatArgs<Types>(_values)...));
	}
	
	// Constructors
	FString() = default;
	FString(std::string const& _str);
	FString(DefaultChar const* _str) : str(_str) {}
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
