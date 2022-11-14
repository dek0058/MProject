#pragma once
#include "BaseException.h"

class NullException : public BaseException {
public:
	NullException(FString const& _object_name, long _line_num, FString const& _file_name)
		: BaseException(_object_name + " is null.", _line_num, _file_name) {
		;
	}
};
