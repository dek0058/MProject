#include "MainFrame.h"


namespace mproject {
namespace ui{

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name) 
	: MWidget(parent, id, title, pos, size, style, name)
{
	this->SetSizeHints(wxSize(200, 100), wxDefaultSize);

	wxBoxSizer* main_sizer;
	main_sizer = new wxBoxSizer(wxVERTICAL);

	message_box = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH2);
	main_sizer->Add(message_box, 1, wxALL | wxEXPAND, 5);

	input_box = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_NO_VSCROLL | wxTE_PROCESS_ENTER);
	main_sizer->Add(input_box, 0, wxALL | wxEXPAND, 5);


	this->SetSizer(main_sizer);
	this->Layout();

	this->Centre(wxBOTH);
}

MainFrame::~MainFrame()
{
}


}	// ui
}	// mproject

