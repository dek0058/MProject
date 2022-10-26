#include "TestFrame.h"
#include "TestApplication/Administrator.h"
#include "TestApplication/Server/TestEngine.h"

namespace mproject {
namespace ui {

TestFrame::TestFrame(wxWindow* parent) : MainFrame(parent) {
	msg.Clear();
}

void TestFrame::OnInitialize() {
	
	Show();

	AddLog(FString(pTEXT("Initialize TestFrame!")));
	
	//AddLog(FString(pTEXT("Ready TestEngine!")));
	//
	//Administrator::GetMutableInstance().StartEngine();
	

}

void TestFrame::AddLog(FString const& _string) {
	
	if (msg.length() >= FString::max_size) {
		// TODO
	}

	msg += _string.Data() + pTEXT("\r\n");
	message_box->ChangeValue(msg);
}


}	// ui
}	// mproject
