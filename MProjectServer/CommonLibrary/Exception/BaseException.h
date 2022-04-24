#pragma once
#include <exception>
#include <string>
#include <array>

#include "GuardDefine.h"

constexpr long Unknown_Line_Number = -1;
constexpr char const * Unknown_File_Name = "<unknown>";

class BaseException : public std::exception {
public:
	BaseException(std::string const& _message = "", long _line_num = Unknown_Line_Number, std::string const& _file_name = Unknown_File_Name)
		: VAR_INIT(message), VAR_INIT(line_num), VAR_INIT(file_name) { 
		data_line_number_array.fill(0);
	}
	BaseException(std::string const& _message, long _line_num, long _data_line_number, std::string const& _file_name)
		: VAR_INIT(message), VAR_INIT(line_num), VAR_INIT(file_name) {
		data_line_number_array[0] = _data_line_number;
		data_line_number_array[1] = 0;
	}
	BaseException(std::string const& _message, long _line_num, long _data1_line_number, long _data2_line_number, std::string const& _file_name)
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

	char const* what() const throw() {
		return message.c_str();
	}

	long GetLineNumber() const {
		return line_num;
	}
	long GetDataLineNumber(unsigned short _index = 0) const {
		return data_line_number_array[_index];
	}
	std::string const& GetFileNmae() const {
		return file_name;
	}

private:
	std::string message;
	long line_num;
	std::array<long, 2> data_line_number_array;
	std::string file_name;
};