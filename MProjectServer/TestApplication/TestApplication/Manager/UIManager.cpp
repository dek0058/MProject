#include "UIManager.h"

#include <wx/event.h>

#include "TestApplication/UI/Frame/TestFrame.h"



namespace mproject {

UIManager::~UIManager() {
	
}

void UIManager::Start() {
	
	main_widget = Create<ui::TestFrame>(nullptr);


}

}	// mproject

