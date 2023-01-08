
using System;
using System.Net;

namespace mproject {

    using network;
    using logger;
    using System.Threading;

    internal class Program {

        public static int Main ( string[] args ) {

            ConsoleLogger logger = new ();

            Socket<FHeader> socket = new (1024, 1024, new TimeSpan(0, 0, 5), logger) ;

            Int32 port = 7778;
            IPEndPoint ip_endpoint = new(IPAddress.IPv6Loopback, port);
            socket.Connect(ip_endpoint);

            Int32 Count = 0;
            while ( Count++ < 100 ) {
                Thread.Sleep(1000);
            }

            socket.Close();

            return 0;
        }
    }
}
