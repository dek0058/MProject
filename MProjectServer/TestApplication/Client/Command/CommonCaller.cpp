#include "CommonCaller.h"
#include "CommandMacro.h"
#include "Client/Administrator.h"
#include "String/StringUtility.h"

namespace mproject {




void CommonCaller::Initialize(CommandManager* _command_manager) {
	ADD_COMMAND(_command_manager, Help);
}

void CommonCaller::Help::Execute(std::optional<FCommand> _command) {
	if (!_command) {
		return;
	}

	if (_command->Size() > 0) {
		return;
	}

	FString command = _command->command;
	Administrator::GetMutableInstance().WriteLog_Info(pTEXT("# Command List"));
	return CommandManager::GetConstInstance().ForEach([command](FString const& _str, std::shared_ptr<CommandCaller> _caller) {
		Administrator::GetMutableInstance().WriteLog_Info(StringFormat::Format(pTEXT("{}:{}"), _str.data, _caller->help().data));
	});
}

}	// mproject
