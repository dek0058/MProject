/*****************************************************************//**
 * \file   Command.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-11-01
 *********************************************************************/

#pragma once

#include "TestApplication/ServerDefine.h"


namespace mproject {

struct FCommand {

	FCommand(std::span<FString> _command);
	
	template<typename T>
		requires std::is_integral_v<T>
	T Get(size_t _index) const {
		if (_index >= arguments.size()) {
			return T();
		}
		return std::stoi(arguments[_index].data);
	}

	template<typename T>
		requires std::is_floating_point_v<T>
	T Get(size_t _index) const {
		if (_index >= arguments.size()) {
			return T();
		}
		return std::stof(arguments[_index].data);
	}

	FString Get(size_t _index) const {
		if (_index >= arguments.size()) {
			return FString();
		}
		return arguments[_index];
	}

	FString ToString() const {
		FString result = command;
		for (auto& arg : arguments) {
			result += FString(pTEXT(" ")) + arg;
		}
		return result;
	}

	FString command;
	std::vector<FString> arguments;
	StringKey key;
};

}	// mproject
