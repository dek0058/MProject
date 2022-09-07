#include <wx/wx.h>
#include <wx/sizer.h>

#include <wx/msw/stattext.h>
#include <wx/msw/frame.h>

class App : public wxApp {
public:
	bool OnInit() {
		
		wxFrame* window = new wxFrame(nullptr, wxID_ANY, "GUI Test");
		//wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		//wxStaticText* text = new wxStaticText(window, wxID_ANY, "Well Don\nEverything seems to be working", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
		//text->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
		//sizer->Add(text);
		
		window->Show();
		return true;
	}

};

wxIMPLEMENT_APP(App);
