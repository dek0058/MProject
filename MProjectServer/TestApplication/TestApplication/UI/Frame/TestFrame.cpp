#include "TestFrame.h"
#include "String/StringEnum.h"
#include "String/StringFormat.h"
#include "MProjectLogger/Core/ILogger.h"
#include "TestApplication/Administrator.h"
#include "TestApplication/Server/TestEngine.h"

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
		AddLog(StringFormat::Format(pTEXT("[{}]{}"), StringEnum::ToString<logger::ELogLevel>(level).Data(), msg.Data()));
	}

	// 테스트용
	//GetLogger()->WriteLog(logger::ELogLevel::Info, FString(pTEXT("Test Log!")));

}


void TestFrame::AddLog(FString const& _string) {
	AddLog(wxString(_string.Data()));
}

void TestFrame::AddLog(wxString const& _string) {
	message_box->ChangeValue(message_box->GetValue() + wxString(_string + pTEXT("\r\n")));
	if (!message_box->CanScroll(wxVERTICAL)) {
		message_box->ScrollLines(message_box->GetScrollRange(wxVERTICAL));
	}
}

std::shared_ptr<logger::ILogger> TestFrame::GetLogger() {
	return logger.lock();
}

}	// ui
}	// mproject
