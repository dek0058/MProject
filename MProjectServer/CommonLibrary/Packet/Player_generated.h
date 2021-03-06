// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_PLAYER_MPROJECT_PACKET_H_
#define FLATBUFFERS_GENERATED_PLAYER_MPROJECT_PACKET_H_

#include "flatbuffers/flatbuffers.h"

#include "Core_generated.h"

namespace MProject {
namespace Packet {

struct GPC;
struct GPCBuilder;

struct GPC FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef GPCBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_USER_KEY = 4
  };
  uint32_t user_key() const {
    return GetField<uint32_t>(VT_USER_KEY, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, VT_USER_KEY, 4) &&
           verifier.EndTable();
  }
};

struct GPCBuilder {
  typedef GPC Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_user_key(uint32_t user_key) {
    fbb_.AddElement<uint32_t>(GPC::VT_USER_KEY, user_key, 0);
  }
  explicit GPCBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<GPC> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<GPC>(end);
    return o;
  }
};

inline flatbuffers::Offset<GPC> CreateGPC(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t user_key = 0) {
  GPCBuilder builder_(_fbb);
  builder_.add_user_key(user_key);
  return builder_.Finish();
}

}  // namespace Packet
}  // namespace MProject

#endif  // FLATBUFFERS_GENERATED_PLAYER_MPROJECT_PACKET_H_
