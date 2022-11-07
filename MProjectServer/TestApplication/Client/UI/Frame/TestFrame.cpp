#include "TestFrame.h"
#include "String/StringUtility.h"
#include "MProjectLogger/Core/ILogger.h"
#include "Client/Administrator.h"
#include "Client/Manager/CommandManager.h"
#include "Client/Command/Command.h"

namespace mproject {
namespace ui {

TestFrame::TestFrame(wxWindow* parent) : MainFrame(parent) {

}

TestFrame::~TestFrame() {

}

void TestFrame::OnInitialize() {
	
	logger = Administrator::GetMutableInstance().GetLogger();

	Show();

	AddLog(FString(pTEXT("Initialize TestFrame!")));

}

void TestFrame::OnTextEnter(wxCommandEvent& _event) {
	MainFrame::OnTextEnter(_event);

	FString msg = FString(input_box->GetValue().c_str().AsWChar());

	AddLog(input_box->GetValue());
	input_box->ChangeValue(wxString());

	std::vector<FString> args; args.reserve(3);
	for (auto arg : StringRange::Split(msg, pTEXT(" "))) {
		args.push_back(FString(DefaultString(arg.begin(), arg.end())));
	}
	
	if (args.empty()) {
		return;
	}

	if (CommandManager::GetMutableInstance().Execute(std::make_optional<FCommand>(args))) {
		AddLog(wxString(pTEXT("Command executed!")));
	}
	else {
		AddLog(wxString(pTEXT("Command failure...")));
	}
}

void TestFrame::OnUpdateUI(wxUpdateUIEvent& _event) {
	MainFrame::OnUpdateUI(_event);

	if (true == logger.expired()) {
		return;
	}

	if (GetLogger()->IsEmpty()) {
		return;
	}

	for (auto& [level, msg] : GetLogger()->GetMessages()) {
		AddLog(StringFormat::Format(pTEXT("[{}]{}"), StringEnum::ToString<logger::ELogLevel>(level).data, msg.data));
	}
}


void TestFrame::AddLog(FString const& _string) {
	AddLog(wxString(_string.data));
}

void TestFrame::AddLog(wxString const& _string) {
	message_box->ChangeValue(message_box->GetValue() + wxString(_string + pTEXT("\r\n")));
	message_box->SetInsertionPointEnd();
}

std::shared_ptr<logger::ILogger> TestFrame::GetLogger() {
	return logger.lock();
}

}	// ui
}	// mproject
