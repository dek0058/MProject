/*****************************************************************//**
 * \file   StringRange.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-11-01
 *********************************************************************/
#pragma once


#include "String.h"
#include "GuardDefine.h"

#include <ranges>


class StringRange {
	DELETE_REFERENCE_CREATOR(StringRange);

	template<typename T>
		requires DefaultStringType<T>
	using SplitView = std::ranges::split_view<std::ranges::ref_view<T const>, std::ranges::owning_view<T>>;

public:
	
	static SplitView<DefaultString> Split(const FString& str, const FString& delimiter) {
		return str.data | std::views::split(delimiter.data);
	}

	template<typename T>
		requires DefaultStringType<T>
	static SplitView<T> Split(const FString& str, T delimiter) {
		return str.data | std::views::split(delimiter);
	}

};
