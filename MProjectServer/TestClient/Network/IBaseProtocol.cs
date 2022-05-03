using System;

namespace TestClient.Network {
    
    public interface IBaseProtocol {
        public byte[] GetHashCodeArray();
        public string GetHashCodeString();
        public UInt32 GetPacketTag();
        
        public void SetHashCodeArray(byte[] _hash_code);

    }
}
