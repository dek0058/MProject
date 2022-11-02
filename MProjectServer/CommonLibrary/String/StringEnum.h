/*****************************************************************//**
 * \file   StringEnum.h
 * \brief  Enum to FString convert
 * 
 * \author dek0058
 * \date   2022-10-31
 *********************************************************************/
#pragma once

#include "String.h"
#include "GuardDefine.h"

#include "Utility/magic_enum.hpp"

#include <concepts>

class StringEnum {
	DELETE_REFERENCE_CREATOR(StringEnum);

public:

	template<typename T>
		requires std::is_enum_v<T>
	_NODISCARD static FString ToString(std::integral auto _enum) {
		return FString(magic_enum::enum_name<T>(static_cast<T>(_enum)));
	}

	template<typename T>
		requires std::is_enum_v<T>
	_NODISCARD static FString ToString(T _enum) {
		return FString(magic_enum::enum_name<T>(_enum));
	}

	template<typename T>
		requires std::is_enum_v<T>
	_NODISCARD static T ToEnum(FString const& _string) {
		return magic_enum::enum_cast<T>(_string.ToString()).value_or(static_cast<T>(0));
	}

};
