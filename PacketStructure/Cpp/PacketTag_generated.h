// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_PACKETTAG_MPROJECT_PACKET_H_
#define FLATBUFFERS_GENERATED_PACKETTAG_MPROJECT_PACKET_H_

#include "flatbuffers/flatbuffers.h"

namespace MProject {
namespace Packet {

struct FProtocol;
struct FProtocolBuilder;

struct NProtocolMessage;
struct NProtocolMessageBuilder;

enum Tag : uint32_t {
  Tag_Create = 0,
  Tag_Test = 1,
  Tag_MIN = Tag_Create,
  Tag_MAX = Tag_Test
};

inline const Tag (&EnumValuesTag())[2] {
  static const Tag values[] = {
    Tag_Create,
    Tag_Test
  };
  return values;
}

inline const char * const *EnumNamesTag() {
  static const char * const names[3] = {
    "Create",
    "Test",
    nullptr
  };
  return names;
}

inline const char *EnumNameTag(Tag e) {
  if (flatbuffers::IsOutRange(e, Tag_Create, Tag_Test)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesTag()[index];
}

struct FProtocol FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FProtocolBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TAG = 4,
    VT_HASH_CODE = 6
  };
  uint32_t tag() const {
    return GetField<uint32_t>(VT_TAG, 0);
  }
  const flatbuffers::Vector<uint8_t> *hash_code() const {
    return GetPointer<const flatbuffers::Vector<uint8_t> *>(VT_HASH_CODE);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, VT_TAG, 4) &&
           VerifyOffset(verifier, VT_HASH_CODE) &&
           verifier.VerifyVector(hash_code()) &&
           verifier.EndTable();
  }
};

struct FProtocolBuilder {
  typedef FProtocol Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_tag(uint32_t tag) {
    fbb_.AddElement<uint32_t>(FProtocol::VT_TAG, tag, 0);
  }
  void add_hash_code(flatbuffers::Offset<flatbuffers::Vector<uint8_t>> hash_code) {
    fbb_.AddOffset(FProtocol::VT_HASH_CODE, hash_code);
  }
  explicit FProtocolBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FProtocol> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FProtocol>(end);
    return o;
  }
};

inline flatbuffers::Offset<FProtocol> CreateFProtocol(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t tag = 0,
    flatbuffers::Offset<flatbuffers::Vector<uint8_t>> hash_code = 0) {
  FProtocolBuilder builder_(_fbb);
  builder_.add_hash_code(hash_code);
  builder_.add_tag(tag);
  return builder_.Finish();
}

inline flatbuffers::Offset<FProtocol> CreateFProtocolDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t tag = 0,
    const std::vector<uint8_t> *hash_code = nullptr) {
  auto hash_code__ = hash_code ? _fbb.CreateVector<uint8_t>(*hash_code) : 0;
  return MProject::Packet::CreateFProtocol(
      _fbb,
      tag,
      hash_code__);
}

struct NProtocolMessage FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef NProtocolMessageBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_PROTOCOL = 4
  };
  const flatbuffers::Vector<flatbuffers::Offset<MProject::Packet::FProtocol>> *protocol() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<MProject::Packet::FProtocol>> *>(VT_PROTOCOL);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_PROTOCOL) &&
           verifier.VerifyVector(protocol()) &&
           verifier.VerifyVectorOfTables(protocol()) &&
           verifier.EndTable();
  }
};

struct NProtocolMessageBuilder {
  typedef NProtocolMessage Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_protocol(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MProject::Packet::FProtocol>>> protocol) {
    fbb_.AddOffset(NProtocolMessage::VT_PROTOCOL, protocol);
  }
  explicit NProtocolMessageBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<NProtocolMessage> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<NProtocolMessage>(end);
    return o;
  }
};

inline flatbuffers::Offset<NProtocolMessage> CreateNProtocolMessage(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MProject::Packet::FProtocol>>> protocol = 0) {
  NProtocolMessageBuilder builder_(_fbb);
  builder_.add_protocol(protocol);
  return builder_.Finish();
}

inline flatbuffers::Offset<NProtocolMessage> CreateNProtocolMessageDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<MProject::Packet::FProtocol>> *protocol = nullptr) {
  auto protocol__ = protocol ? _fbb.CreateVector<flatbuffers::Offset<MProject::Packet::FProtocol>>(*protocol) : 0;
  return MProject::Packet::CreateNProtocolMessage(
      _fbb,
      protocol__);
}

inline const MProject::Packet::NProtocolMessage *GetNProtocolMessage(const void *buf) {
  return flatbuffers::GetRoot<MProject::Packet::NProtocolMessage>(buf);
}

inline const MProject::Packet::NProtocolMessage *GetSizePrefixedNProtocolMessage(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<MProject::Packet::NProtocolMessage>(buf);
}

inline bool VerifyNProtocolMessageBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<MProject::Packet::NProtocolMessage>(nullptr);
}

inline bool VerifySizePrefixedNProtocolMessageBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<MProject::Packet::NProtocolMessage>(nullptr);
}

inline void FinishNProtocolMessageBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<MProject::Packet::NProtocolMessage> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedNProtocolMessageBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<MProject::Packet::NProtocolMessage> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace Packet
}  // namespace MProject

#endif  // FLATBUFFERS_GENERATED_PACKETTAG_MPROJECT_PACKET_H_
