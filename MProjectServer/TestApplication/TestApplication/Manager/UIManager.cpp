#include "UIManager.h"

#include "TestApplication/UI/Frame/TestFrame.h"

namespace mproject {

UIManager::~UIManager() {
	m_frame_map.clear();
}

void UIManager::Start() {
	
	std::shared_ptr main = Create<ui::TestFrame>(nullptr);

	

}

}	// mproject

