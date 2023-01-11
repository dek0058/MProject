/*****************************************************************//**
 * \file   DuplicateException.h
 * \brief  
 * 
 * \author dek0058
 * \date   2023-01-11
 *********************************************************************/
#pragma once
#include "BaseException.h"

class DuplicateException : public BaseException {
public:
	DuplicateException(FString const& _object_name, long _line_num, FString const& _file_name)
		: BaseException(_object_name + L" is duplicate.", _line_num, _file_name) {
		;
	}

	DuplicateException(FString const& _object_name, FString const& _key_name, long _line_num, FString const& _file_name)
		: BaseException(_object_name + L"'s " + _key_name + L" is duplicate.", _line_num, _file_name) {
		;
	}
};
