﻿#include <wx/wx.h>
#include "TestApplication/Administrator.h"

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
	mproject::Administrator::GetMutableInstance().Finalize();
	return 0;
}
