/*****************************************************************//**
 * \file   MainFrame.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-10-17
 *********************************************************************/

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>

#include "TestApplication/UI/Parent/MWidget.h"

namespace mproject {
namespace ui {

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public MWidget
{
private:

protected:
	wxTextCtrl* message_box;
	wxTextCtrl* input_box;

	// Virtual event handlers, override them in your derived class
	virtual void OnTextEnter(wxCommandEvent& event) { event.Skip(); }
	virtual void OnUpdateUI(wxUpdateUIEvent& event) { event.Skip(); }

public:

	MainFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(800, 500), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL, const wxString& name = wxT("Main"));

	~MainFrame();

};

}	// ui
}	// mproject
