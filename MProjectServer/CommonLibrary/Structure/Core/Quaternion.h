#pragma once
#include "Packet/Core_generated.h"

using namespace MProject;

struct FQuaternion {
	float x, y, z, w;

	FQuaternion() : x(0.0F), y(0.0F), z(0.0F), w(0.0F) {}
	FQuaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	FQuaternion(Packet::FQuaternion const* _target) : x(_target->x()), y(_target->y()), z(_target->z()), w(_target->w()) {}

	void operator=(FQuaternion const& _target) {
		x = _target.x;
		y = _target.y;
		z = _target.z;
		w = _target.w;
	}

	flatbuffers::Offset<Packet::FQuaternion> ToFaltbuffer(flatbuffers::FlatBufferBuilder& _builder) {
		return Packet::CreateFQuaternion(_builder, x, y, z, w);
	}
};

