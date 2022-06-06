#pragma once
#include "Vector.h"
#include "Quaternion.h"

using namespace MProject;

struct FTransform {

	FVector position;
	FQuaternion rotation;
	FVector scale;

	FTransform() {}
	FTransform(Packet::FTransform const* _target) : position(_target->position()), rotation(_target->rotation()), scale(_target->scale()) {}

	void operator=(FTransform const& _target) {
		position = _target.position;
		rotation = _target.rotation;
		scale = _target.scale;
	}

	flatbuffers::Offset<Packet::FTransform> ToFaltbuffer(flatbuffers::FlatBufferBuilder& _builder) {
		return Packet::CreateFTransform(_builder, position.ToFaltbuffer(_builder), rotation.ToFaltbuffer(_builder), scale.ToFaltbuffer(_builder));
	}
};

