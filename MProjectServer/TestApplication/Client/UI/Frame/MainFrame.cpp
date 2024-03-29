﻿#include "MainFrame.h"


namespace mproject {
namespace ui{

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name) 
	: MWidget(parent, id, title, pos, size, style, name)
{
	this->SetSizeHints(wxSize(200, 100), wxDefaultSize);

	wxBoxSizer* main_sizer;
	main_sizer = new wxBoxSizer(wxVERTICAL);

	message_box = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_AUTO_URL | wxTE_CHARWRAP | wxTE_LEFT | wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH2);
	main_sizer->Add(message_box, 1, wxALL | wxEXPAND, 5);

	input_box = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_NO_VSCROLL | wxTE_PROCESS_ENTER);
	main_sizer->Add(input_box, 0, wxALL | wxEXPAND, 5);


	this->SetSizer(main_sizer);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	message_box->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MainFrame::OnUpdateUI), NULL, this);
	input_box->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(MainFrame::OnTextEnter), NULL, this);
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	message_box->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MainFrame::OnUpdateUI), NULL, this);
	input_box->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(MainFrame::OnTextEnter), NULL, this);

}


}	// ui
}	// mproject

