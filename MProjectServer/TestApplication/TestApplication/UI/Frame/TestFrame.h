/*****************************************************************//**
 * \file   TestFrame.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-10-17
 *********************************************************************/

#pragma once
#include "TestApplication/ServerDefine.h"
#include "TestApplication/UI/Frame/MainFrame.h"

namespace mproject {
namespace ui {

class TestFrame : public MainFrame {
	
public:
	
	TestFrame(wxWindow* parent);
	
public:

	virtual void OnInitialize() override;

private:
	
	void AddLog(FString const& _string);


private:
	wxString msg;

};

}	// ui
}	// mproject
