using System;
using System.Collections.Generic;
using System.Text;

namespace TestClient.Network {
    public struct FPacket {
        public UInt32 tag;
        public UInt32 length;
        public byte[] hash_code;
        public byte[] data;

        public FPacket(UInt32 _tag, UInt32 _length, byte[] _hash_code, byte[] _data) {
            tag = 0;
            length = 0;
            hash_code = _hash_code;
            data = _data;
        }
    }
}
