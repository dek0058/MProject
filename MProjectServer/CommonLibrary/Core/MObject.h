#pragma once

#include <boost/uuid/uuid.hpp>
#include <string>

class MObject {
public:
	MObject();
	~MObject();
	
public: //! Operator
	bool operator==(MObject const& _rhs) const {
		return tag == _rhs.tag;
	}
	
	MObject& operator=(MObject const& _rhs) {
		tag = _rhs.tag;
		return *this;
	}

public:	//! Getter
	bool IsInitialize() const {
		return is_initialize;
	}
	bool IsDestroy() const {
		return is_destroy;
	}

	std::string ToString() const;
	std::wstring ToWString() const;

public:
	void Initialize() {
		is_initialize = true;
		OnInitialize();
	}
	void Destroy() {
		is_destroy = true;
		OnDestroy();
	}

	
protected:
	
	virtual void OnInitialize() {};
	virtual void OnDestroy() {};

private:
	boost::uuids::uuid tag;
	bool is_initialize = false;
	bool is_destroy = false;
};
