// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace MProject.Packet
{

using global::System;
using global::System.Collections.Generic;
using global::FlatBuffers;

public struct FHashCode : IFlatbufferObject
{
  private Struct __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public void __init(int _i, ByteBuffer _bb) { __p = new Struct(_i, _bb); }
  public FHashCode __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public sbyte HashCode(int j) { return __p.bb.GetSbyte(__p.bb_pos + 0 + j * 1); }

  public static Offset<MProject.Packet.FHashCode> CreateFHashCode(FlatBufferBuilder builder, sbyte[] HashCode) {
    builder.Prep(1, 32);
    for (int _idx0 = 32; _idx0 > 0; _idx0--) {
      builder.PutSbyte(HashCode[_idx0-1]);
    }
    return new Offset<MProject.Packet.FHashCode>(builder.Offset);
  }
}


}