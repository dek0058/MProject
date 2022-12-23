using mproject.utility;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Threading;
using TestClient.Network;

namespace mproject {
    namespace network {


        public class Socket<THeader> where THeader : struct, IHeader {

            private ulong receive_packet_capacity;
            private ulong max_packet_size;
            private uint heartbeat_second;
            private bool listening;

            private Socket socket;
            private EndPoint remote_endpoint;
            private System.Threading.Timer timer;
            
            private FPeer self;
            private byte[] receive_buffer;
            private List<FPeer> peers;

            delegate void ReceiveHandlerType ( in Packet<THeader> _packet, int _bytes, in FPeer _peer );
            delegate void ConnectionHandlerType ( in FPeer _peer );
            delegate void DisconnectionHandlerType ( in FPeer _peer );
            delegate void TimeoutHandlerType ( in FPeer _peer );

            private ReceiveHandlerType receive_handler;
            private ConnectionHandlerType connection_handler;
            private DisconnectionHandlerType disconnection_handler;
            private TimeoutHandlerType timeout_handler;


            public Socket (
                EndPoint _endpoint,
                ulong _receive_packet_capacity,
                ulong _max_packet_size,
                uint _heartbeat_second = 5
            ) {


            }

            public void Open ( AddressFamily _address_family ) {
                socket = new Socket ( _address_family, SocketType.Dgram, ProtocolType.Udp );
            }

            public void Close ( ) {
                PacketMessage<THeader> message = new PacketMessage<THeader> ( Self.guid, PacketMessageType.DISCONNECTION_TYPE );
                AsyncSendToAll ( message.Bytes );

                listening = false;
            }

            public void Connect ( EndPoint _endpoint ) {
                socket.Connect ( _endpoint );

                PacketMessage<THeader> message = new PacketMessage<THeader> ( Self.guid, PacketMessageType.CONNECTION_TYPE );
                AsyncSendTo ( message.Bytes, _endpoint );

                listening = true;

                HeartBeat ( );
                Receive ( );
            }

            public void Bind ( EndPoint _endpoint ) {
                socket.Bind ( _endpoint );
            }

            public void AsyncSendTo ( ReadOnlySpan<byte> _buffer_span, EndPoint _endpoint ) {
                socket.SendTo ( _buffer_span, SocketFlags.None, _endpoint );
            }

            public void AsyncSendToAll ( ReadOnlySpan<byte> _buffer_span) {
                for(int i = 0; i < peers.Count; ++i ) {
                    AsyncSendTo ( _buffer_span, peers[i].endpoint );
                }
            }

            ref readonly FPeer Self { get => ref self; }



            private void OnReceive ( IAsyncResult _result ) {
                if ( !_result.IsCompleted ) {

                    return;
                }

                try {
                    int recv = socket.EndReceive ( _result );
                    ReadOnlySpan<byte> datas = new ( receive_buffer );
                    Packet<THeader> packet = new ( datas[..recv].ToArray ( ) );

                    FPeer? peer = peers.Find ( ( FPeer _peer ) => {
                        if ( _peer.guid == packet.Header.UUID ) {
                            _peer.last_packet_timestamp = DateTime.Now;
                            return true;
                        }
                        return false;
                    } );

                    if ( peer == null ) {
                        peers.Add ( new ( remote_endpoint, packet.Header.UUID, DateTime.Now ) );
                        peer = peers.Last ( );

                        if ( connection_handler != null ) {
                            connection_handler ( peer.Value );
                            PacketMessage<THeader> message = new ( Self.guid, PacketMessageType.CONNECTION_TYPE );
                            AsyncSendTo ( message.Bytes, peer?.endpoint );
                        }
                    }

                    bool is_a_user_message = true;
                    if(recv - Marshal.SizeOf<THeader>() == sizeof ( uint ) ) {
                        uint message = BitConverter.ToUInt32 ( packet.Buffer );
                        if( message == PacketMessageType.CONNECTION_TYPE || message == PacketMessageType.KEEP_ALIVE_TYPE) {
                            is_a_user_message = false;
                        } else if(message == PacketMessageType.DISCONNECTION_TYPE) {
                            is_a_user_message = false;
                            disconnection_handler?.Invoke ( peer.Value );

                            peers.RemoveAll ( ( FPeer _peer ) => {
                                return _peer.guid == peer?.guid;
                            } );
                        }
                    }

                    if(is_a_user_message && receive_buffer != null) {
                        receive_handler ( packet, recv, peer.Value );    
                    }
                } catch(Exception) {
                    
                }

                if(listening) {
                    Receive ( );
                }

            }

            private void Receive ( ) {
                try {
                    var result = socket.BeginReceiveFrom ( receive_buffer, 0, receive_buffer.Length, SocketFlags.None, ref remote_endpoint, new AsyncCallback ( OnReceive ), null );
                } catch(Exception) {
                    
                }
            }

            private void OnHeartBeat( IAsyncResult _result ) {
                
            }

            private void HeartBeat() {
                
            }

        }


    }   // network
}       // mproject
