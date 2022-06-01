#pragma once
#include "Packet/Core_generated.h"

using namespace MProject;

struct FVector {
	float x, y, z;

	FVector() : x(0.0F), y(0.0F), z(0.0F) {}
	FVector(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	FVector(Packet::Vector const* _target) : x(_target->x()), y(_target->y()), z(_target->z()) {}

	void operator=(FVector const& _target) {
		x = _target.x;
		y = _target.y;
		z = _target.z;
	}

	flatbuffers::Offset<Packet::Vector> ToFaltbuffer(flatbuffers::FlatBufferBuilder& _builder) {
		return Packet::CreateVector(_builder, x, y, z);
	}
};


