#include "ServerCaller.h"
#include "TestApplication/Manager/CommandManager.h"
#include "String/StringHash.h"
#include "String/StringAlgorithm.h"


namespace {
template<typename T>
	requires std::derived_from<T, mproject::CommandCaller>
void AddCommand(mproject::CommandManager* _command_manager, FString const& _str) {
	_command_manager->RegisterCommand<T>(StringHash::Hash(StringAlgorithm::ToLowerCopy(_str)));
}
}
#define ADD_COMMAND(manager, class_type) AddCommand<class_type>(_command_manager, pTEXT(#class_type));


namespace mproject {

void ServerCaller::Initialize(CommandManager* _command_manager) {
	auto a = StringAlgorithm::ToLowerCopy(pTEXT("EngineStart"));
	auto b = StringHash::Hash(a);

	ADD_COMMAND(_command_manager, EngineStart);
}


bool ServerCaller::EngineStart::Execute(std::optional<FCommand> _command) {

	

	return true;
}

}	// mproject
