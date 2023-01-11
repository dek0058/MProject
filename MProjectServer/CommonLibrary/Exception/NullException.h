/*****************************************************************//**
 * \file   NullException.h
 * \brief  
 * 
 * \author dek0058
 * \date   2023-01-11
 *********************************************************************/
#pragma once
#include "BaseException.h"

class NullException : public BaseException {
public:
	NullException(FString const& _object_name, long _line_num, FString const& _file_name)
		: BaseException(_object_name + L" is null.", _line_num, _file_name) {
		;
	}
};
