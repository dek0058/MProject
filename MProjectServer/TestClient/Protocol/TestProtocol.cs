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
    public class TestProtocol : BaseProtocol {

        public static byte[] Hash_Code = new byte[GlobalDefine.PACKET_HASH_CODE_SIZE];
        
        static public FPacket CreatePacket(Int32 _x, Int32 _y, Int32 _z) {
            var builder = new FlatBufferBuilder(GlobalDefine.PACKET_MAX_SIZE);
            NTestPacket.StartNTestPacket(builder);
            NTestPacket.AddX(builder, _x);
            NTestPacket.AddY(builder, _y);
            NTestPacket.AddZ(builder, _z);
            var packet_offset = NTestPacket.EndNTestPacket(builder);

            builder.Finish(packet_offset.Value);
            var buffer = builder.DataBuffer;

            var packet = new FPacket(1, Convert.ToUInt32(buffer.Length - buffer.Position), TestProtocol.Hash_Code, buffer.ToSizedArray());
            return packet;
        }
        

    }
    
    public class TestProtocolHandler {
        
    }

}
