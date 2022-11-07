#include "MWidget.h"
#include "Client/Manager/UIManager.h"


namespace mproject {
namespace ui {


MWidget::MWidget(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxFrame(parent, id, title, pos, size, style, name), is_being_destroyed(false) {
	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MWidget::OnDestroy));
}

MWidget::~MWidget() {
	Disconnect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MWidget::OnDestroy));
}

void MWidget::OnDestroy(wxCloseEvent& _event) {
	is_being_destroyed = true;
	UIManager::GetMutableInstance().Destroy(GetId());
	_event.Skip();
}

}	// ui
}	// mproject

