#include <wx/wx.h>
#include "Client/Administrator.h"

class App : public wxApp {
public:
	bool OnInit();
	int OnExit();

};

wxIMPLEMENT_APP(App);


bool App::OnInit() {


	

	return mproject::Administrator::GetMutableInstance().Initialize();
}

int App::OnExit() {
	return mproject::Administrator::GetMutableInstance().Finalize();
}
