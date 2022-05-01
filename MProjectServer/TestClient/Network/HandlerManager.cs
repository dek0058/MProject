using System;
using System.Collections.Generic;
using System.Text;

using MProject.Packet;
using TestClient.Network;

namespace TestClient.Network {
    public class HandlerManager {

        private SortedDictionary<(Tag, string/*HashCode*/), BaseProtocol> handler_map;

        public HandlerManager() {
            //handler_map = new SortedDictionary<(UInt32, string), BaseProtocol>();
        }
        
        public void RegisterHandler(Tag _tag, BaseProtocol _handler) {
            
            
            //handler_map.Add((_tag, ""), _handler);
        }

        public void UnregisterHanlder() {
            
        }

        public void ReceivePacket(FPacket _packet) {
        
        }
    }
}
