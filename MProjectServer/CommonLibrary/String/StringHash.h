/*****************************************************************//**
 * \file   StringHash.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-11-02
 *********************************************************************/
#pragma once
#include "String.h"
#include "GuardDefine.h"

#include <functional>

class StringHash {
	DELETE_REFERENCE_CREATOR(StringHash)
public:

	_NODISCARD static size_t Hash(const FString& str) {
		return std::hash<DefaultString>{}(str.data);
	}
};
