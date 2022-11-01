/*****************************************************************//**
 * \file   UIManager.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-10-31
 *********************************************************************/

#pragma once

#include <wx/defs.h>

#include "TestApplication/ServerDefine.h"
#include "Utility/TSingleton.h"
#include "TestApplication/UI/Parent/MWidget.h"


namespace mproject {

using ParentWidget = ui::MWidget;

template<typename T>
concept Widget = std::is_base_of_v<ParentWidget, T>;

class UIManager : public TSingleton<UIManager> {
public:
	UIManager();
	~UIManager();

public:
	/**
	 * \brief Default UI를 생성합니다.
	 */
	void Start();

	template<typename T, typename... Types>
		requires Widget<T>
	T* Create(Types&&... _values) {
		auto data = new T(std::forward<Types>(_values)...);
		if (nullptr == data) {
			return nullptr;
		}
		data->OnInitialize();
		frame_map.emplace(data->GetId(), data);
		return data;
	}

	void Destroy(wxWindowID _id) {
		auto iter = frame_map.find(_id);
		if (iter == frame_map.end()) {
			return;
		}
		if (false == iter->second->IsBeingDestroyed()) {
			iter->second->Close(false);
			return;
		}
		iter->second->OnFinalize();
		frame_map.erase(iter);
	}

	template<typename T, typename... Types>
		requires Widget<T>
	T* Find(wxWindowID _id) {
		auto iter = frame_map.find(_id);
		if (iter == frame_map.end()) {
			return nullptr;
		}
		return static_cast<T>(iter->second);
	}

	/**
	 * \brief	최상단 위젯.
	 */
	ParentWidget* GetMainWidget() {
		return main_widget;
	}


private:
	hashmap<wxWindowID, ParentWidget*> frame_map;
	ParentWidget* main_widget = nullptr;

};

}	// mproject
