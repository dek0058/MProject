#include "Command.h"
#include "String/StringUtility.h"

namespace mproject {

FCommand::FCommand(std::span<FString> _command) {
	if (_command.empty()) {
		return;
	}
	command = StringAlgorithm::ToLowerCopy(_command[0]);
	if (_command.size() > 1) {
		arguments = std::vector<FString>(_command.begin() + 1, _command.end());
	}
}

}	// mproject
