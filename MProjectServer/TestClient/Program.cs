


using mproject.network;
using mproject.utility;
using System;
using System.Data;

namespace mproject {

    using network;
    using System.Net;
    using System.Reflection.PortableExecutable;
    using System.Threading;

    internal class Program {

        public static int Main ( string[] args ) {


            Socket<FHeader> socket = new ( 1024, 1024, TimeSpan.FromSeconds ( 5 ) );

            IPEndPoint IP_endpoint = new ( IPAddress.IPv6Loopback, 7778 );
            socket.Connect ( IP_endpoint );

            Thread.Sleep ( new TimeSpan ( 0, 0, 10 ) );

            Console.WriteLine ( "연결끊김" );

            return 0;
        }
    }
}
