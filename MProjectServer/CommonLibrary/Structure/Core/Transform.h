#pragma once
#include "Vector.h"
#include "Quaternion.h"

using namespace MProject;

struct FTransform {

	FVector position;
	FQuaternion rotation;
	FVector scale;

	FTransform() {}
	FTransform(Packet::Transform const* _target) : position(_target->position()), rotation(_target->rotation()), scale(_target->scale()) {}

	void operator=(FTransform const& _target) {
		position = _target.position;
		rotation = _target.rotation;
		scale = _target.scale;
	}

	flatbuffers::Offset<Packet::Transform> ToFaltbuffer(flatbuffers::FlatBufferBuilder& _builder) {
		return Packet::CreateTransform(_builder, position.ToFaltbuffer(_builder), rotation.ToFaltbuffer(_builder), scale.ToFaltbuffer(_builder));
	}
};

