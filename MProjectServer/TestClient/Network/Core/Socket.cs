using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Threading.Tasks;

namespace mproject {
    using System.Threading;
    using logger;

    namespace network {


        public class Socket<THeader> where THeader : struct, IHeader {

            private readonly Int32 receive_packet_capacity;
            private readonly Int32 max_packet_size;
            private readonly TimeSpan heartbeat_timespan;
            private bool listening;

            private Socket socket;
            private EndPoint remote_endpoint;
            private Task deadline_timer;
            private CancellationTokenSource cancel_token = new ();

            private FPeer self;
            private byte[] receive_buffer;
            private List<FPeer> peers = new(1);

            delegate void ReceiveHandlerType(in Packet<THeader> _packet, int _bytes, in FPeer _peer);
            delegate void ConnectionHandlerType(in FPeer _peer);
            delegate void DisconnectionHandlerType(in FPeer _peer);
            delegate void TimeoutHandlerType(in FPeer _peer);

            private ReceiveHandlerType receive_handler = null;
            private ConnectionHandlerType connection_handler = null;
            private DisconnectionHandlerType disconnection_handler = null;

            private ILogger logger = null;

            public Socket(
                Int32 _receive_packet_capacity,
                Int32 _max_packet_size,
                TimeSpan _heartbeat_timespan,
                ILogger _logger
            ) {
                logger = _logger;

                receive_packet_capacity = _receive_packet_capacity;
                max_packet_size = _max_packet_size;
                heartbeat_timespan = _heartbeat_timespan;

                receive_buffer = new byte[receive_packet_capacity];
                self = new(new IPEndPoint(IPAddress.IPv6Loopback, 0));
                socket = new Socket(AddressFamily.InterNetworkV6, SocketType.Dgram, ProtocolType.Udp);
            }

            public void Dispose() {
                if ( cancel_token != null ) {
                    cancel_token.Cancel();
                    deadline_timer.Wait();
                    cancel_token.Dispose();
                }
            }

            public void Close() {
                PacketMessage<THeader> message = new PacketMessage<THeader>(Self.guid, PacketMessageType.DISCONNECTION_TYPE);
                AsyncSendToAll(message.Bytes);
                listening = false;
            }

            public void Connect(EndPoint _endpoint) {
                remote_endpoint = _endpoint;

                PacketMessage<THeader> message = new PacketMessage<THeader>(Self.guid, PacketMessageType.CONNECTION_TYPE);
                AsyncSendTo(message.Bytes, remote_endpoint);

                listening = true;

                HeartBeat();
                Receive();
            }

            public void AsyncSendTo(ReadOnlySpan<byte> _buffer_span, EndPoint _endpoint) {
                try {
                    socket.SendTo(_buffer_span, SocketFlags.None, _endpoint);
                } catch ( Exception _e ) {
                    logger?.WriteLog(ELogLevel.Error, _e.Message);
                }
            }

            public void AsyncSendToAll(ReadOnlySpan<byte> _buffer_span) {
                for ( int i = 0; i < peers.Count; ++i ) {
                    AsyncSendTo(_buffer_span, peers[i].endpoint);
                }
            }

            ref readonly FPeer Self { get => ref self; }

            private void OnReceive(IAsyncResult _result) {
                try {
                    if ( !_result.IsCompleted ) {
                        throw new Exception("Receive is failure!");
                    }

                    Socket client_socket = _result.AsyncState as Socket;
                    int recv = client_socket.EndReceive(_result);
                    if ( recv > max_packet_size ) {
                        throw new Exception($"bytes transferred size is over! Packet:{recv} MaxPacket:{max_packet_size}");
                    }

                    ReadOnlySpan<byte> datas = new(receive_buffer);
                    Packet<THeader> packet = new(datas[..recv].ToArray());

                    FPeer? peer = peers.Find((FPeer _peer) => {
                        if ( _peer.guid == packet.Header.UUID ) {
                            _peer.last_packet_timestamp = DateTime.Now;
                            return true;
                        }
                        return false;
                    });

                    if ( peer == null ) {
                        peers.Add(new(remote_endpoint, packet.Header.UUID, DateTime.Now));
                        peer = peers.Last();

                        if ( connection_handler != null ) {
                            connection_handler(peer.Value);
                            PacketMessage<THeader> message = new(Self.guid, PacketMessageType.CONNECTION_TYPE);
                            AsyncSendTo(message.Bytes, peer?.endpoint);
                        }
                    }

                    bool is_a_user_message = true;
                    if ( recv - Marshal.SizeOf<THeader>() == sizeof(uint) ) {
                        uint message = BitConverter.ToUInt32(packet.Buffer);
                        if ( message == PacketMessageType.CONNECTION_TYPE || message == PacketMessageType.KEEP_ALIVE_TYPE ) {
                            is_a_user_message = false;
                        } else if ( message == PacketMessageType.DISCONNECTION_TYPE ) {
                            is_a_user_message = false;
                            disconnection_handler?.Invoke(peer.Value);

                            peers.RemoveAll((FPeer _peer) => {
                                return _peer.guid == peer?.guid;
                            });
                        }
                    }

                    if ( is_a_user_message && receive_buffer != null ) {
                        receive_handler(packet, recv, peer.Value);
                    }
                } catch ( Exception _e ) {
                    logger?.WriteLog(ELogLevel.Error, _e.Message);
                }

                if ( listening ) {
                    Receive();
                }
            }

            private void Receive() {
                try {
                    AsyncCallback callback = new (OnReceive);
                    object? state = socket;
                    var result = socket.BeginReceiveFrom(receive_buffer, 0, receive_buffer.Length, SocketFlags.None, ref remote_endpoint, callback, state);

                    //Task.Factory.StartNew(socket.ReceiveFromAsync(receive_buffer, SocketFlags.None, remote_endpoint, ));

                } catch ( Exception _e ) {
                    logger?.WriteLog(ELogLevel.Error, _e.Message);
                }
            }

            private void HeartBeat() {
                deadline_timer = Task.Factory.StartNew(async () => {
                    while ( listening ) {
                        if ( cancel_token.Token.IsCancellationRequested ) {
                            return;
                        }

                        peers.RemoveAll((FPeer _peer) => {
                            if ( _peer.last_packet_timestamp + heartbeat_timespan < DateTime.Now ) {
                                disconnection_handler?.Invoke(_peer);
                                return true;
                            }
                            return false;
                        });

                        PacketMessage<THeader> message = new(Self.guid, PacketMessageType.KEEP_ALIVE_TYPE);
                        AsyncSendToAll(message.Bytes);

                        await Task.Delay(heartbeat_timespan);
                    }
                }, cancel_token.Token, TaskCreationOptions.LongRunning, TaskScheduler.Default);
            }
        }
    }   // network
}       // mproject
