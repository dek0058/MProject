using System;
using System.Net;
using System.Net.Sockets;

namespace TestClient {
    internal class Program {
        static void Main(string[] args) {

            IPAddress address = new IPAddress(new byte[] { 127, 0, 0, 1 });
            Console.WriteLine(address.ToString());
            IPEndPoint ip_end_point = new IPEndPoint(address, 3333);

            TcpClient client = new TcpClient();

            Console.WriteLine("Conneting server...");
            try
            {
                client.Connect(ip_end_point);
                Console.WriteLine("Connet server!");

            }
            catch (SocketException _exception) {
                Console.WriteLine(_exception.ToString());
            } finally { 
                if(true == client.Connected) {
                    client.Close();
                }
            }
        }
    }
}
