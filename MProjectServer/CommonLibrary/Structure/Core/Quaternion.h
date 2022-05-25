#pragma once
#include "Packet/Core_generated.h"

using namespace MProject;

struct FQuaternion {
	float x, y, z, w;

	FQuaternion() : x(0.0F), y(0.0F), z(0.0F), w(0.0F) {}

	flatbuffers::Offset<Packet::Quaternion> ToFaltbuffer(flatbuffers::FlatBufferBuilder& _builder) {
		return Packet::CreateQuaternion(_builder, x, y, z, w);
	}
};

