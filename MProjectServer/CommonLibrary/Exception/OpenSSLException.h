#pragma once
#include "BaseException.h"


class SHA256Exception : public BaseException {
public:
	SHA256Exception(long _line_num = Unknown_Line_Number, std::string const& _file_name = Unknown_File_Name) 
		: BaseException ("SHA-256 Error", _line_num, _file_name) { ; }
};
