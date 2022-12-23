/*****************************************************************//**
 * \file   Peer.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-12-23
 *********************************************************************/
using System;
using System.Net;

namespace mproject {
    namespace network {
        
        public struct FPeer {
            public Guid guid;
            public EndPoint endpoint;
            public DateTime last_packet_timestamp;

            public FPeer ( ) =>
                (guid, endpoint, last_packet_timestamp) = (Guid.Empty, null, DateTime.Now);

            public FPeer ( EndPoint _endpoint ) =>
                (guid, endpoint, last_packet_timestamp) = (Guid.NewGuid ( ), _endpoint, DateTime.Now);

            public FPeer(EndPoint _endpoint, Guid _guid) =>
                (guid, endpoint, last_packet_timestamp) = (_guid, _endpoint, DateTime.Now);
            
            public FPeer( EndPoint _endpoint, Guid _guid, DateTime _timestamp ) =>
                (guid, endpoint, last_packet_timestamp) = (_guid, _endpoint, _timestamp);
        }

    }   // network
}       // mproject