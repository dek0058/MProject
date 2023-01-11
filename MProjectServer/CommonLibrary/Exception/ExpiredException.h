/*****************************************************************//**
 * \file   ExpiredException.h
 * \brief  
 * 
 * \author dek0058
 * \date   2023-01-11
 *********************************************************************/
#pragma once
#include "BaseException.h"

class ExpiredException : public BaseException {
public:
	ExpiredException(FString const& _object_name, long _line_num, FString const& _file_name)
		: BaseException(_object_name + L" is expired.", _line_num, _file_name) { ; }
};
