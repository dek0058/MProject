/*****************************************************************//**
 * \file   ExpiredException.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-10-05
 * \version 0.1
 *********************************************************************/

#pragma once
#include "BaseException.h"
#include <format>

class ExpiredException : public BaseException {
public:
	ExpiredException(std::string const& type_name, long _line_num = Unknown_Line_Number, std::string const& _file_name = Unknown_File_Name)
		: BaseException(std::format("{} is expired.", type_name), _line_num, _file_name) {
		;
	}
};
