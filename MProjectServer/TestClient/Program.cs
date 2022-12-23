


using mproject.network;
using mproject.utility;
using System;
using System.Data;

namespace mproject {

    
    
    internal class Program {

        public static int Main ( string[] args ) {

            /*
            1000895125765816517867138112231141842305701291248425
Lenth:24
100089512576581651786713811223114184230570

            1291248425=424967297
Lenth:20
1_4c193359-a53a-43b2-8a70-e70eb8e63900 
             
            */

            Guid guid = Guid.NewGuid ( );

            {
                PacketMessage<FHeader> message = new ( guid, PacketMessageType.DISCONNECTION_TYPE );

                var datas = message.Bytes;

                foreach ( var item in datas ) {
                    Console.WriteLine ( item );
                }
                Console.WriteLine ( $"\nLenth:{datas.Length}" );

                FHeader temp = ConvertUtility.ToObject<FHeader> ( datas.Slice ( 0, 20 ).ToArray ( ) );
                Console.WriteLine ( $"{temp.Protocol_ID}_{temp.UUID}" );

                uint message_type = BitConverter.ToUInt32 ( datas.ToArray(), 20 );
                Console.WriteLine ( $"{message_type}" );

            }

            {
                FHeader header = new ( guid );

                byte[] datas = ConvertUtility.ToBytes ( header );
                foreach ( var item in datas ) {
                    Console.Write ( item );
                }
                Console.WriteLine ( $"\nLenth:{datas.Length}" );

                FHeader temp = ConvertUtility.ToObject<FHeader> ( datas );

                Console.WriteLine ( $"{temp.Protocol_ID}_{temp.UUID}" );
            }
           

           

            return 0;
        }
    }
}
