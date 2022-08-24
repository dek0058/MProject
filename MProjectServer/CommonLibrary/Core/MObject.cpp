#include "MObject.h"
#include <random>

#include "cctz/time_zone.h"
#include "cctz/civil_time_detail.h"
#include <boost/uuid/uuid_generators.hpp>

MObject::MObject() 
	: tag(boost::uuids::basic_random_generator<std::mt19937_64>()()) {
}

MObject::~MObject() {
	if (!IsDestroy()) {
		Destroy();
	}
	tag = boost::uuids::nil_generator()();
}

