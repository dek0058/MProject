﻿/*****************************************************************//**
 * \file   StringFormat.h
 * \brief  FString format
 * 
 * \author dek0058
 * \date   2022-10-31
 *********************************************************************/
#pragma once

#include "String.h"
#include "GuardDefine.h"

#include <format>
#include <iterator>
#include <numeric>

using Default_Fmt_it = std::back_insert_iterator<std::_Fmt_buffer<DefaultChar>>;
using Default_Context = std::basic_format_context<Default_Fmt_it, DefaultChar>;
using Default_Args = std::basic_format_args<Default_Context>;
template<typename... Types>
using Format_Args = std::_Format_arg_store<Default_Context, Types...>;

class StringFormat {
	DELETE_REFERENCE_CREATOR(StringFormat);

public:

	template<typename... Types>
	_NODISCARD static FString Format(DefaultChar const* _format, Types&&... _values) {
		return FString(std::vformat(_format, Format_Args<Types...> { (_values)... }));
	}
	template<typename... Types>
	_NODISCARD static FString Format(DefaultString const& _format, Types&&... _values) {
		return FString(std::vformat(_format, Format_Args<Types...> { (_values)... }));
	}
	template<typename... Types>
	_NODISCARD static FString Format(FString const& _format, Types&&... _values) {

		return FString(std::vformat(_format.data, Format_Args<Types...> { (_values)... }));
	}

	template<typename T>
		requires DefaultStringType<T>
	_NODISCARD static FString Join(std::span<T> _list, T const& _delimiter) {
		return FString(std::accumulate(std::next(_list.begin()), _list.end(), _list[0], [&_delimiter](T& _lhs, T& _rhs) {
			return _lhs + _delimiter + _rhs;
		}));
	}
	template<typename T>
		requires DefaultStringType<T>
	_NODISCARD static FString Join(std::span<T> _list, FString const& _delimiter) {
		return FString(std::accumulate(std::next(_list.begin()), _list.end(), _list[0], [&_delimiter](T& _lhs, T& _rhs) {
			return _lhs + _delimiter.data + _rhs;
		}));
	}
	template<typename T>
		requires DefaultStringType<T>
	_NODISCARD static FString Join(std::span<FString> _list, T const& _delimiter) {
		return std::accumulate(std::next(_list.begin()), _list.end(), _list[0], [&_delimiter](FString& _lhs, FString& _rhs) {
			return _lhs.data + _delimiter + _rhs.data;
		});
	}
};
