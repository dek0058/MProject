/*****************************************************************//**
 * \file   UIManager.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-10-17
 *********************************************************************/

#pragma once

#include "TestApplication/ServerDefine.h"
#include "Utility/TSingleton.h"
#include "TestApplication/UI/Interface/IWidget.h"

#include <wx/defs.h>

class wxFrame;

namespace mproject {

template<typename T>
concept Widget = std::is_base_of_v<ui::IWidget, T> && std::is_base_of_v<wxFrame, T>;

class UIManager : public TSingleton<UIManager> {
public:
	~UIManager();

public:
	/**
	 * \brief Default UI를 생성합니다.
	 * 
	 */
	void Start();

	template<typename T, typename... Types>
		requires Widget<T>
	std::shared_ptr<T> Create(Types&&... _values) {
		auto data = std::shared_ptr<wxFrame>(new T(std::forward<Types>(_values)...));
		if (nullptr == data.get()) {
			return std::shared_ptr<T>();
		}
		m_frame_map.emplace(data->GetId(), data);
		auto result = std::static_pointer_cast<T>(data);
		result->OnInitialize();
		return result;
	}

	void Destroy(wxWindowID _id) {
		auto iter = m_frame_map.find(_id);
		if (iter == m_frame_map.end()) {
			return;
		}
		m_frame_map.erase(iter);
	}

	template<typename T, typename... Types>
		requires Widget<T>
	std::shared_ptr<T> Find(wxWindowID _id) {
		auto iter = m_frame_map.find(_id);
		if (iter == m_frame_map.end()) {
			return std::shared_ptr<T>();
		}
		auto result = std::static_pointer_cast<T>(iter->second);
		return result;
	}



private:

	hashmap<wxWindowID, std::shared_ptr<wxFrame>> m_frame_map;

};

}	// mproject
