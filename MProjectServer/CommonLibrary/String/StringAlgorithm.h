/*****************************************************************//**
 * \file   StringAlgorithm.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-11-03
 *********************************************************************/
#pragma once

#include "String.h"
#include "GuardDefine.h"

class StringAlgorithm {
	DELETE_REFERENCE_CREATOR(StringAlgorithm);

public:

	static FString& ToUpper(FString& _str);
	static FString& ToLower(FString& _str);

	_NODISCARD static FString ToUpper_Copy(FString const& _str);
	_NODISCARD static FString ToLowerCopy(FString const& _str);


private:

	static void ToUpper(std::basic_string<char>& _str);
	static void ToUpper(std::basic_string<wchar_t>& _str);

	static void ToLower(std::basic_string<char>& _str);
	static void ToLower(std::basic_string<wchar_t>& _str);
};
