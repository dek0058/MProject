#pragma once
#include "Vector.h"
#include "Quaternion.h"

using namespace MProject;

struct FTransform {

	FVector position;
	FQuaternion rotation;
	FVector scale;

	flatbuffers::Offset<Packet::Transform> ToFaltbuffer(flatbuffers::FlatBufferBuilder& _builder) {
		return Packet::CreateTransform(_builder, position.ToFaltbuffer(_builder), rotation.ToFaltbuffer(_builder), scale.ToFaltbuffer(_builder));
	}
};

