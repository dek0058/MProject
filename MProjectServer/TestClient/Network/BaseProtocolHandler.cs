using System;
using System.Collections.Generic;
using System.Text;

namespace TestClient.Network {
    public class BaseProtocolHandler {
        private IBaseProtocol base_protocol;
        public IBaseProtocol BaseProtocol {
            get { return base_protocol; }
        }

        public BaseProtocolHandler(IBaseProtocol _protocol)
            => base_protocol = _protocol;

        public byte[] GetHashCodeArray() {
            return BaseProtocol.GetHashCodeArray();
        }

        public string GetHashCodeString() {
            return BaseProtocol.GetHashCodeString();
        }

        public UInt32 GetPacketTag() {
            return BaseProtocol.GetPacketTag();
        }

        public void SetHashCodeArray(byte[] _hash_code) {
            BaseProtocol.SetHashCodeArray(_hash_code);
        }
            

        public virtual void ReceivePacket(FPacket _packet) { ; }
    }

    
}
