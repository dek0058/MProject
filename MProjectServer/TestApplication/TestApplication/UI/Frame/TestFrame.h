/*****************************************************************//**
 * \file   TestFrame.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-10-17
 *********************************************************************/

#pragma once
#include "TestApplication/ServerDefine.h"
#include "UI/Frame/MainFrame.h"
#include "TestApplication/UI/Interface/IWidget.h"

namespace mproject {
namespace ui {

class TestFrame : public MainFrame, IWidget {
	
public:
	
	TestFrame(wxWindow* parent);
	
public:

	virtual void OnInitialize() override;

};

}	// ui
}	// mproject
