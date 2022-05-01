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


            //! IOCP
            base.Completed += OnReceive;
            socket.ReceiveAsync(this);

        }

        public async void Accept() {
            socket.Bind(ip_end_point);
            socket.Listen(max_packet_size);
            await socket.AcceptAsync();
        }

        public void Disconnect() {
            socket.Disconnect(false);
            socket.Close();
        }

        void SendPacket(FPacket _packet) {
            
            

            //socket.Send(, , SocketFlags.None);
            
        }


        private void OnReceive(object _sender, SocketAsyncEventArgs _args) {
            if (false == socket.Connected) {
                Console.WriteLine("Disconnect server...");
                return;
            }

            byte[] data = _args.Buffer;
            

        }
    }
}
