// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_ACTOR_MPROJECT_PACKET_H_
#define FLATBUFFERS_GENERATED_ACTOR_MPROJECT_PACKET_H_

#include "flatbuffers/flatbuffers.h"

#include "Core_generated.h"

namespace MProject {
namespace Packet {

struct Actor;
struct ActorBuilder;

struct Actor FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ActorBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_ACTOR_KEY = 4,
    VT_USER_KEY = 6,
    VT_TRANSFORM = 8
  };
  uint32_t actor_key() const {
    return GetField<uint32_t>(VT_ACTOR_KEY, 0);
  }
  uint32_t user_key() const {
    return GetField<uint32_t>(VT_USER_KEY, 0);
  }
  const MProject::Packet::FTransform *transform() const {
    return GetPointer<const MProject::Packet::FTransform *>(VT_TRANSFORM);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, VT_ACTOR_KEY, 4) &&
           VerifyField<uint32_t>(verifier, VT_USER_KEY, 4) &&
           VerifyOffset(verifier, VT_TRANSFORM) &&
           verifier.VerifyTable(transform()) &&
           verifier.EndTable();
  }
};

struct ActorBuilder {
  typedef Actor Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_actor_key(uint32_t actor_key) {
    fbb_.AddElement<uint32_t>(Actor::VT_ACTOR_KEY, actor_key, 0);
  }
  void add_user_key(uint32_t user_key) {
    fbb_.AddElement<uint32_t>(Actor::VT_USER_KEY, user_key, 0);
  }
  void add_transform(flatbuffers::Offset<MProject::Packet::FTransform> transform) {
    fbb_.AddOffset(Actor::VT_TRANSFORM, transform);
  }
  explicit ActorBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Actor> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Actor>(end);
    return o;
  }
};

inline flatbuffers::Offset<Actor> CreateActor(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t actor_key = 0,
    uint32_t user_key = 0,
    flatbuffers::Offset<MProject::Packet::FTransform> transform = 0) {
  ActorBuilder builder_(_fbb);
  builder_.add_transform(transform);
  builder_.add_user_key(user_key);
  builder_.add_actor_key(actor_key);
  return builder_.Finish();
}

}  // namespace Packet
}  // namespace MProject

#endif  // FLATBUFFERS_GENERATED_ACTOR_MPROJECT_PACKET_H_
