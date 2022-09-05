#pragma once
#include "GlobalDefine.h"
#include <concepts>

namespace mproject {
namespace logger {

template<typename T>
concept is_str = std::same_as<T, char*>
				|| std::same_as<T, wchar_t*>
				|| std::same_as<T, char const*>
				|| std::same_as<T, wchar_t const*>
				|| std::same_as<T, std::string>
				|| std::same_as<T, std::string const>
				|| std::same_as<T, std::wstring>
				|| std::same_as<T, std::wstring const>;

//template<typename T>
//struct is_str : std::integral_constant<bool, false> {};
//template<> struct is_str<char*> : std::integral_constant<bool, true> {};
//template<> struct is_str<wchar_t*> : std::integral_constant<bool, true> {};
//template<> struct is_str<const char*> : std::integral_constant<bool, true> {};
//template<> struct is_str<std::string> : std::integral_constant<bool, true> {};
//template<> struct is_str<const std::string> : std::integral_constant<bool, true> {};
//template<> struct is_str<std::wstring> : std::integral_constant<bool, true> {};
//template<> struct is_str<const std::wstring> : std::integral_constant<bool, true> {};

enum class ELogLevel : byte {
	Trace,
	Debug,
	Info,
	Warning,
	Error,
	Critical,
};
	

}	// logger
}	// mproject

