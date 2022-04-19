using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;

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
                client.ConnectAsync("127.0.0.1", 3333);

                while(true)
                {
                    String msg = Console.ReadLine();
                    if (msg == "exit")
                    {
                        break;
                    }
                    NetworkStream stream = client.GetStream();
                    byte[] send = System.Text.Encoding.ASCII.GetBytes(msg);
                    stream.Write(send, 0, send.Length);
                    
                    byte[] recv = new byte[1024];
                    stream.ReadAsync(recv, 0, recv.Length);
                    Thread.Sleep(10);
                    Console.WriteLine(System.Text.Encoding.ASCII.GetString(recv));
                    Console.WriteLine("-echo-");
                }
            }
            catch (SocketException _exception) {
                Console.WriteLine(_exception.ToString());
            } finally { 

            }
            client.Close();
            
        }
    }
}
