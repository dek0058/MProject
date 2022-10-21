#include "MWidget.h"
#include "TestApplication/Manager/UIManager.h"


namespace mproject {
namespace ui {


MWidget::MWidget(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxFrame(parent, id, title, pos, size, style, name) {
	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MWidget::OnDestroy));
}

MWidget::~MWidget() {
	Disconnect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MWidget::OnDestroy));
}

void MWidget::OnDestroy(wxCloseEvent& _event) {
	UIManager::GetMutableInstance().Destroy(GetId());
	_event.Skip();
}

}	// ui
}	// mproject

