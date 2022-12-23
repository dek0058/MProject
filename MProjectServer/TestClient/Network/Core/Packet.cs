/*****************************************************************//**
 * \file   Packet.h
 * \brief  Network packet data.
 * 
 * \author dek0058
 * \date   2022-12-23
 *********************************************************************/
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.InteropServices;

namespace mproject {
    using System.IO;
    using System.Linq;
    using System.Reflection.PortableExecutable;
    using utility;

    namespace network {

        public interface IHeader {
            public uint Protocol_ID { get; }
            public uint Protocol { get; }
            public Guid UUID { get; set; }
        }

        [StructLayout ( LayoutKind.Explicit, Pack = 4, Size = 20 )]
        public struct FHeader : IHeader {
            [FieldOffset ( 0 )]
            public uint protocol;
            [FieldOffset ( 4 )]
            public Guid guid;

            public FHeader ( ) =>
                (protocol, guid) = (Protocol_ID, Guid.Empty);

            public FHeader ( Guid _guid ) =>
                (protocol, guid) = (Protocol_ID, _guid);

            public uint Protocol_ID { get => 1; }
            public uint Protocol { get => protocol; }
            public Guid UUID { get => guid; set => guid = value; }
        }


        public class Packet<THeader> where THeader : struct, IHeader {

            private readonly THeader header;
            private readonly byte[] buffer;

            public Packet ( byte[] _buffer ) {
                int header_length = Marshal.SizeOf<THeader> ( );
                if ( _buffer.Length < header_length ) {
                    throw new InvalidDataException ( new string("Packet buffer is too small.") );
                }

                header = ConvertUtility.ToObject<THeader> ( _buffer );
                if(header.Protocol != header.Protocol_ID) {
                    throw new InvalidDataException ( new string ( "Packet protocol is not correct." ) );
                }

                var buffer_span = new Span<byte> ( _buffer );
                buffer = buffer_span.Slice ( header_length, _buffer.Length ).ToArray ( );
            }

            public ref readonly THeader Header { get => ref header; }
            public ref readonly byte[] Buffer { get => ref buffer; }
        }

        public struct PacketMessage<THeader> where THeader : struct, IHeader {

            public THeader header;
            public uint message;

            public PacketMessage ( Guid _guid, uint _message ) {
                header = new ( ) {
                    UUID = _guid
                };
                message = _message;
            }

            public ReadOnlySpan<byte> Bytes {
                get {
                    var header_bytes = ConvertUtility.ToBytes ( header );
                    var message_bytes = BitConverter.GetBytes ( message );
                    var result = new byte[header_bytes.Length + message_bytes.Length];
                    header_bytes.CopyTo ( result, 0 );
                    message_bytes.CopyTo ( result, header_bytes.Length );
                    return result;
                }
            }
        }

        public static class PacketMessageType {
            public const uint KEEP_ALIVE_TYPE = 424967295;
            public const uint CONNECTION_TYPE = 424967296;
            public const uint DISCONNECTION_TYPE = 424967297;
        }

    }
}
