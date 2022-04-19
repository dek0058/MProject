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
                    byte[] data = System.Text.Encoding.ASCII.GetBytes(msg);
                    stream.Write(data, 0, data.Length);
                    //Thread.Sleep(1000);
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
