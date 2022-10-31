/*****************************************************************//**
 * \file   TestFrame.h
 * \brief  Test console app.
 * 
 * \author dek0058
 * \date   2022-10-31
 *********************************************************************/

#pragma once
#include "TestApplication/ServerDefine.h"
#include "TestApplication/UI/Frame/MainFrame.h"

namespace mproject {

namespace logger {
class ILogger;
}	// logger

namespace ui {

class TestFrame : public MainFrame {
	
public:
	
	TestFrame(wxWindow* parent);
	~TestFrame();

public:

	virtual void OnInitialize() override;

protected:

	virtual void OnTextEnter(wxCommandEvent& _event) override;
	virtual void OnUpdateUI(wxUpdateUIEvent& _event) override;

private:
	
	void AddLog(FString const& _string);
	void AddLog(wxString const& _string);

	std::shared_ptr<logger::ILogger> GetLogger();

private:

	std::weak_ptr<logger::ILogger> logger;

};

}	// ui
}	// mproject
