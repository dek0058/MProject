#include "Command.h"
#include "String/StringHash.h"
#include "String/StringAlgorithm.h"


namespace mproject {

FCommand::FCommand(std::span<FString> _command) : key(0) {
	if (_command.empty()) {
		return;
	}
	command = StringAlgorithm::ToLowerCopy(_command[0]);
	key = StringHash::Hash(command);
	if (_command.size() > 1) {
		arguments = std::vector<FString>(_command.begin() + 1, _command.end());
	}
}

}	// mproject
