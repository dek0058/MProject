#include "MObject.h"

#include <random>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

MObject::MObject() 
	: tag(boost::uuids::basic_random_generator<std::mt19937_64>()()) {
}

MObject::~MObject() {
	if (!IsDestroy()) {
		Destroy();
	}
	tag = boost::uuids::nil_generator()();
}


std::string MObject::ToString() const {
	return boost::uuids::to_string(tag);
}

std::wstring MObject::ToWString() const {
	return boost::uuids::to_wstring(tag);
}

