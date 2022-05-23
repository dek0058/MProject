using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;
using System.Net;

namespace TestClient
{
    using Network;
    //using Protocol;
    using Utility;

    public class GameSocket : SocketAsyncEventArgs {
        
        private Socket socket;
        private IPEndPoint ip_end_point;
        private int max_packet_size;
        

        // [TODO] 이거 나중에 다른 클래스로 빼야함
        private HandlerManager handler_manager = new HandlerManager();
        public HandlerManager HandlerManager {
            get { return handler_manager; }
        }

        public GameSocket(IPAddress _ip_address, int _port, int _max_packet_size) {

            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            ip_end_point = new IPEndPoint(_ip_address, _port);
            max_packet_size = _max_packet_size;

            RemoteEndPoint = ip_end_point;

            //! IOCP
            Completed += OnConnected;
            //socket.ReceiveAsync(this);

            // Test
            handler_manager.RegisterHandler((UInt32)MProject.Packet.Tag.Create, new ProtocolMessageHandler());
            //handler_manager.RegisterHandler((UInt32)MProject.Packet.Tag.Test, new TestProtocolHandler());

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

        public void SendPacket(FPacket _packet) {
            byte[] tag = BitConverter.GetBytes(_packet.tag);
            byte[] legnth = BitConverter.GetBytes(_packet.length);
            List<byte> data = new List<byte>();
            data.AddRange(tag);
            data.AddRange(legnth);
            data.AddRange(_packet.hash_code);
            data.AddRange(_packet.data);

            byte[] buffer = data.ToArray();
            socket.Send(buffer, SocketFlags.None);
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

            //_args.bu\

            var buffer = new Span<byte>(_args.Buffer);

            UInt32 tag = BitConverter.ToUInt32(buffer.Slice(0, GlobalDefine.PACKET_TAG_SIZE));
            UInt32 size = BitConverter.ToUInt32(buffer.Slice(GlobalDefine.PACKET_TAG_SIZE, GlobalDefine.PACKET_LEGNTH_SIZE));
            byte[] hash_code = buffer.Slice(8, GlobalDefine.PACKET_HASH_CODE_SIZE).ToArray();
            byte[] data = buffer.Slice(GlobalDefine.PACKET_HEADER_SIZE, Convert.ToInt32(size)).ToArray();
            FPacket packet = new FPacket(tag, size, hash_code, data);
            handler_manager.ReceivePacket(packet);
            socket.ReceiveAsync(this);
        }
    }
}
