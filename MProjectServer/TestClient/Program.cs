using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace TestClient {
    using Utility;
    //using Protocol;
    using Network;

    internal class Program {
        static public GameSocket socket;

        
        class ObjectA {
        
            public virtual void Print(int id, string msg, int[] arr) {
                // TODO
            }

            public void Print(Action<int, string, int[]> action) {
                // TODO
            }

        }


        class ObjectB : ObjectA {
            public override void Print ( int id, string msg, int[] arr ) {
                // TODO
            }
        }
        
        
        


        static void Main(string[] args) {


            IPAddress address = new IPAddress(new byte[] { 127, 0, 0, 1 });
            socket = new GameSocket(address, 3333, GlobalDefine.PACKET_MAX_SIZE);
            try {
                ConsoleKeyInfo cki;
                socket.Accept();
                bool loop = true;
                while (loop) {

                    cki = Console.ReadKey(true);

                    
                    switch(cki.Key) {
                        case ConsoleKey.LeftArrow: {
                            loop = false;
                        } break;
                        case ConsoleKey.RightArrow: {
                           // socket.SendPacket(TestProtocol.CreatePacket(10, 5, 3));
                        }
                        break;
                    }

                    Thread.Sleep(10);
                }
            
            } catch (SocketException _exception) {
                Console.WriteLine(_exception.ToString());
            } finally {
                socket.Disconnect();
            }

            //Protocol.TestProtocol testProtocol;


            //Console.WriteLine(UniversalToolkit.Digest2Hex(MSHA256.GenerateHashcode("TestProtocol")));

        }
    }
}


/*
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
*/