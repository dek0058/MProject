#pragma once
#include "Packet/Core_generated.h"

using namespace MProject;

struct FVector {
	float x, y, z;

	FVector() : x(0.0F), y(0.0F), z(0.0F) {}

	flatbuffers::Offset<Packet::Vector> ToFaltbuffer(flatbuffers::FlatBufferBuilder& _builder) {
		return Packet::CreateVector(_builder, x, y, z);
	}
};


