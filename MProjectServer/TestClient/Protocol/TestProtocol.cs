using System;
using System.Collections.Generic;
using System.Text;

using System.Runtime.Serialization;
using System.Security.Cryptography;    

using MProject.Packet;
using TestClient.Network;
using FlatBuffers;

using TestClient.Utility;

namespace TestClient.Protocol {
    public class TestProtocol : IBaseProtocol {

        private static byte[] Hash_Code_Array = new byte[GlobalDefine.PACKET_HASH_CODE_SIZE];
        static UInt32 Packet_Tag = (UInt32)Tag.Test;

        public byte[] GetHashCodeArray() {
            return Hash_Code_Array;
        }

        public string GetHashCodeString() {
            return UniversalToolkit.Digest2Hex(Hash_Code_Array);
        }

        public uint GetPacketTag() {
            return Packet_Tag;
        }

        public void SetHashCodeArray(byte[] _hash_code) {
            Hash_Code_Array = _hash_code;
        }


        static public FPacket CreatePacket(Int32 _x, Int32 _y, Int32 _z) {
            var builder = new FlatBufferBuilder(GlobalDefine.PACKET_MAX_SIZE);
            NTestPacket.StartNTestPacket(builder);
            NTestPacket.AddX(builder, _x);
            NTestPacket.AddY(builder, _y);
            NTestPacket.AddZ(builder, _z);
            var packet_offset = NTestPacket.EndNTestPacket(builder);

            builder.Finish(packet_offset.Value);
            var buffer = builder.DataBuffer;

            var packet = new FPacket(Packet_Tag, Convert.ToUInt32(buffer.Length - buffer.Position), TestProtocol.Hash_Code_Array, buffer.ToSizedArray());

            Console.WriteLine("Tag:{0}, Length:{1}", packet.tag, packet.length);

            return packet;
        }

        public NTestPacket Deserialize(FPacket _packet) {
            var buffer = _packet.data;
            var packet = NTestPacket.GetRootAsNTestPacket(new ByteBuffer(buffer));
            return packet;
        }
    }
    
    public class TestProtocolHandler : BaseProtocolHandler {
        private TestProtocol protocol_message;

        public TestProtocolHandler() : base(new TestProtocol()) {
            protocol_message = BaseProtocol as TestProtocol;
        }

        public override void ReceivePacket(FPacket _packet) {
            var data = protocol_message.Deserialize(_packet);
            Console.WriteLine("[Receive Packet] tag:{0} length:{1}", _packet.tag, _packet.length);
            Console.WriteLine("[Receive Packet] hash_code:{0}", UniversalToolkit.Digest2Hex(_packet.hash_code));
            Console.WriteLine("X:{0}, Y:{1}, Z:{2}", data.X, data.Y, data.Z);
        }
    }

}
