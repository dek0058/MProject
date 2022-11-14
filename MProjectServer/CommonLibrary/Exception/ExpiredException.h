#pragma once
#include "BaseException.h"

class ExpiredException : public BaseException {
public:
	ExpiredException(FString const& _object_name, long _line_num, FString const& _file_name)
		: BaseException(_object_name + " is expired.", _line_num, _file_name) { ; }
};
