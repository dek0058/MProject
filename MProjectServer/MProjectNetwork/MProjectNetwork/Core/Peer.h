/*****************************************************************//**
 * \file   Peer.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-11-14
 *********************************************************************/
#pragma once

#include "MProjectNetwork/NetworkDefine.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/asio/ip/udp.hpp>

namespace mproject {
namespace network {

struct FPeer {
		
	using UUID = boost::uuids::uuid;
	using EndPoint = boost::asio::ip::udp::endpoint;

	UUID uuid;
	EndPoint endpoint;
	std::chrono::seconds _last_packet_timestamp;


	FPeer() {
		uuid = boost::uuids::nil_uuid();
		endpoint = EndPoint();
		_last_packet_timestamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
	}
	
	FPeer(EndPoint _endpoint, UUID _uuid) 
		: endpoint(_endpoint)
		, uuid(_uuid) {
		_last_packet_timestamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
	}
	
	FPeer(EndPoint _endpoint, UUID _uuid, std::chrono::seconds _timestamp) 
		: endpoint(_endpoint)
		, uuid(_uuid)
		, _last_packet_timestamp(_timestamp) {
	}

};

}	// network
}	// mproject
