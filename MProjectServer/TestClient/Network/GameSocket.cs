using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;
using System.Net;

namespace TestClient
{
    using Network;

    public class GameSocket : SocketAsyncEventArgs {
        
        private Socket socket;
        private IPEndPoint ip_end_point;
        private int max_packet_size;

        public GameSocket(IPAddress _ip_address, int _port, int _max_packet_size) {

            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            ip_end_point = new IPEndPoint(_ip_address, _port);
            max_packet_size = _max_packet_size;

            RemoteEndPoint = ip_end_point;

            //! IOCP
            Completed += OnConnected;
            //socket.ReceiveAsync(this);

        }

        public void Accept() {
            //socket.Bind(ip_end_point);
            //socket.Listen(max_packet_size);
            socket.ConnectAsync(this);
        }

        public void Disconnect() {
            socket.Disconnect(false);
            socket.Close();
        }

        void SendPacket(FPacket _packet) {
            
            

            //socket.Send(, , SocketFlags.None);
            
        }


        private void OnConnected(object _sender, SocketAsyncEventArgs _args) {
            Completed -= OnConnected;
            socket = _args.ConnectSocket;
            UserToken = socket;
            SetBuffer(new byte[max_packet_size], 0, max_packet_size);
            Completed += OnReceive;
            socket.ReceiveAsync(this);
        }

        private void OnReceive(object _sender, SocketAsyncEventArgs _args) {
            if (false == socket.Connected) {
                Console.WriteLine("Disconnect server...");
                return;
            }

            if(_args.Buffer == null) {
                return;
            }

            var buffer = new Span<byte>(_args.Buffer);
            

            UInt32 tag = BitConverter.ToUInt32(buffer.Slice(0, GlobalDefine.PACKET_TAG_SIZE));
            UInt32 size = BitConverter.ToUInt32(buffer.Slice(GlobalDefine.PACKET_TAG_SIZE, GlobalDefine.PACKET_LEGNTH_SIZE));
            byte[] hash_code = buffer.Slice(8, GlobalDefine.PACKET_HASH_CODE_SIZE).ToArray();
            var byte_buffer = new FlatBuffers.ByteBuffer(buffer.Slice(GlobalDefine.PACKET_HEADER_SIZE, Convert.ToInt32(size)).ToArray());
            var ProtocolMessage = MProject.Packet.NProtocolMessage.GetRootAsNProtocolMessage(byte_buffer);

            Console.WriteLine("tag:{0}, size:{1}", tag, size);
            for (Int32 i = 0; i < ProtocolMessage.ProtocolLength; i++) {
                var Protocol = ProtocolMessage.Protocol(i);
                Console.WriteLine("Protocol: {0}", Protocol.Value.Tag);
                StringBuilder sb = new StringBuilder();
                for (Int32 j = 0; j < 32; ++j) {
                    sb.Append(Protocol.Value.HashCode(j).ToString("x2"));
                }
                Console.WriteLine("HashCode: {0}", sb.ToString());
            }

            //ProtocolMessage.Protocol()


            //BitConverter.ToUInt32()


        }
    }
}
