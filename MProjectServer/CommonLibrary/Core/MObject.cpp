#include "MObject.h"

namespace {
	//! Unique ID Generator
	
	size_t GetUniqueID() {
		// TODO
		return 0;
	}

	void RecallUniqueID(size_t& unique_id) {
		// TODO
		unique_id = 0;
	}
}


MObject::MObject() : id(GetUniqueID()) {
	Initialize();
}

MObject::~MObject() {
	Destroy();
	RecallUniqueID(id);
}

