using System;
using System.Collections.Generic;
using System.Text;

using MProject.Packet;
using TestClient.Network;
using TestClient.Utility;

namespace TestClient.Network {
    public class HandlerManager {

        private SortedDictionary<string, BaseProtocolHandler> handler_map = new SortedDictionary<string, BaseProtocolHandler>();
        private SortedDictionary<UInt32, BaseProtocolHandler> handler_tag_map = new SortedDictionary<UInt32, BaseProtocolHandler>();


        public HandlerManager() {
        }
        
        public void RegisterHandler(UInt32 _tag, BaseProtocolHandler _handler) {
            if (handler_tag_map.ContainsKey(_tag)) {
                Console.WriteLine("[HandlerManager] Handler already registered");
                return;
            }
            handler_tag_map.Add(_tag, _handler);
        }

        public void RegisterHandler(UInt32 _tag, byte[] _hash_code) {
            if (!handler_tag_map.ContainsKey(_tag)) {
                Console.WriteLine("[HandlerManager] Handler not registered(tag)");
                return;
            }

            string hash_code_string = UniversalToolkit.Digest2Hex(_hash_code);
            if (handler_map.ContainsKey(hash_code_string)) {
                Console.WriteLine("[HandlerManager] Handler already registered");
                return;
            }

            var handler = handler_tag_map[_tag];
            handler.SetHashCodeArray(_hash_code);
            handler_map.Add(hash_code_string, handler);
        }

        public void UnregisterHanlder(UInt32 _tag) {
            if (!handler_tag_map.ContainsKey(_tag)) {
                Console.WriteLine("[HandlerManager] Handler not registered");
                return;
            }
            handler_tag_map.Remove(_tag);
        }

        public void UnregisterHanlder(string _hash_code) {
            if (!handler_map.ContainsKey(_hash_code)) {
                Console.WriteLine("[HandlerManager] Handler not registered");
                return;
            }
            handler_map.Remove(_hash_code);
        }

        public void ReceivePacket(FPacket _packet) {
            
            if (!handler_tag_map.ContainsKey(_packet.tag)) {
                Console.WriteLine("[HandlerManager] Handler not registered");
                return;
            } else if((Tag)_packet.tag == Tag.Create) {
                handler_tag_map[_packet.tag].ReceivePacket(_packet);
                return;
            }

            string hash_key = UniversalToolkit.Digest2Hex(_packet.hash_code);
            if (!handler_map.ContainsKey(hash_key)) {
                Console.WriteLine("[HandlerManager] No handler for packet");
                return;
            }
            handler_map[hash_key].ReceivePacket(_packet);
        }
    }
}
