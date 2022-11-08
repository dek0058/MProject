#pragma once
#include "String/StringHash.h"
#include "String/StringAlgorithm.h"
#include "CommandCaller.h"
#include "Client/Manager/CommandManager.h"


#define ADD_COMMAND(manager, class_type) AddCommand<class_type>(manager, pTEXT(#class_type));

namespace mproject {

template<typename T>
	requires std::derived_from<T, CommandCaller>
void AddCommand(CommandManager* _manager, FString const& _str) {
	_manager->RegisterCommand<T>(StringHash::Hash(StringAlgorithm::ToLowerCopy(_str)));
}
}

