/*****************************************************************//**
 * \file   IWidget.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-10-21
 *********************************************************************/
#pragma once

#include <wx/frame.h>
#include <wx/event.h>

namespace mproject {
namespace ui {


class MWidget : public wxFrame {
public:
	MWidget(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name);
	~MWidget();

	virtual void OnInitialize() {}
	virtual void OnFinalize() {}

protected:
	void OnDestroy(wxCloseEvent& _event);
};
	
}	// ui
}	// mproject
