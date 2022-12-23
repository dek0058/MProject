using System;
using System.Collections.Generic;
using System.Text;
using MProject.Packet;
using TestClient.Utility;

namespace TestClient.Network {
    public class ProtocolMessageProtocol : IBaseProtocol {
        private static byte[] Hash_Code_Array = new byte[GlobalDefine.PACKET_HASH_CODE_SIZE];
        static UInt32 Packet_Tag = (UInt32)Tag.Create;

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

        public List<(UInt32, byte[])> Deserialize(FPacket _packet) {
            List<(UInt32, byte[])> result = new List<(uint, byte[])>();
            var byte_buffer = new FlatBuffers.ByteBuffer(_packet.data);
            var protocol_message = MProject.Packet.NProtocolMessage.GetRootAsNProtocolMessage(byte_buffer);
            for (Int32 i = 0; i < protocol_message.ProtocolLength; i++) {
                var protocol = protocol_message.Protocol(i);
                var bytes = protocol.Value.GetHashCodeArray();
                result.Add((protocol.Value.Tag, bytes));
            }

            if(Hash_Code_Array == null) {
                Hash_Code_Array = _packet.hash_code;
            }

            return result;
        }
    }

    public class ProtocolMessageHandler : BaseProtocolHandler {
        private ProtocolMessageProtocol protocol_message;

        public ProtocolMessageHandler() : base(new ProtocolMessageProtocol()) {
            protocol_message = BaseProtocol as ProtocolMessageProtocol;
        }

        public override void ReceivePacket(FPacket _packet) {
            //foreach (var (tag, hash_code) in protocol_message.Deserialize(_packet)) {
            //    Program.socket.HandlerManager.RegisterHandler(tag, hash_code);
            //}
        }
    }
}
