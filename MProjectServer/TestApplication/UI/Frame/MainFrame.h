﻿/*****************************************************************//**
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
#include <wx/frame.h>

 ///////////////////////////////////////////////////////////////////////////


 ///////////////////////////////////////////////////////////////////////////////
 /// Class MainFrame
 ///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame
{
private:

protected:
	wxTextCtrl* message_box;
	wxTextCtrl* input_box;

public:

	MainFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(800, 500), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL, const wxString& name = wxT("Main"));

	~MainFrame();

};

