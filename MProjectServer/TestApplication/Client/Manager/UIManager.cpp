#include "UIManager.h"

#include <wx/event.h>

#include "Client/UI/Frame/TestFrame.h"


namespace {
constinit size_t Widget_Capacity = 32;
}

namespace mproject {

UIManager::UIManager() {
	frame_map.reserve(Widget_Capacity);
}

UIManager::~UIManager() {
	
}

void UIManager::Start() {
	
	main_widget = Create<ui::TestFrame>(nullptr);


}

}	// mproject

