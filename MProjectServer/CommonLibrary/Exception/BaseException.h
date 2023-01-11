#pragma once
#include "GlobalDefine.h"
#include "GuardDefine.h"

class BaseException : public std::exception {
public:
	BaseException(FString const& _message, long _line_num, FString const& _file_name)
		: VAR_INIT(message), VAR_INIT(line_num), VAR_INIT(file_name) { 
		data_line_number_array.fill(0);
	}
	BaseException(FString const& _message, long _line_num, long _data_line_number, FString const& _file_name)
		: VAR_INIT(message), VAR_INIT(line_num), VAR_INIT(file_name) {
		data_line_number_array[0] = _data_line_number;
		data_line_number_array[1] = 0;
	}
	BaseException(FString const& _message, long _line_num, long _data1_line_number, long _data2_line_number, FString const& _file_name)
		: VAR_INIT(message), VAR_INIT(line_num), VAR_INIT(file_name) {
		data_line_number_array[0] = _data1_line_number;
		data_line_number_array[1] = _data2_line_number;
	}
	BaseException(BaseException const& _other) 
		: exception(_other) {
		message = _other.message;
		line_num = _other.line_num;
		data_line_number_array = _other.data_line_number_array;
		file_name = _other.file_name;
	}
	virtual ~BaseException() throw() { ; }

	BaseException& operator = (BaseException const& _other) {
		exception::operator=(_other);
		if (&_other != this) {
			message = _other.message;
			line_num = _other.line_num;
			data_line_number_array = _other.data_line_number_array;
			file_name = _other.file_name;
		}
		return *this;
	}

	FString const& Message() const {
		return message;
	}

	long GetLineNumber() const {
		return line_num;
	}
	long GetDataLineNumber(unsigned short _index = 0) const {
		return data_line_number_array[_index];
	}
	FString const& GetFileNmae() const {
		return file_name;
	}

	_NODISCARD virtual FString What() const {
		return L"[" + Message().data + L"]" + L"(" + GetFileNmae().data + L":" + std::to_wstring(GetLineNumber()) + L")";
	}

	_NODISCARD virtual char const* what() const override {
		return "BaseException";
	}

private:
	FString message;
	long line_num;
	std::array<long, 2> data_line_number_array;
	FString file_name;
};