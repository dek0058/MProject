/*****************************************************************//**
 * \file   Packet.h
 * \brief  Network packet data.
 * 
 * \author dek0058
 * \date   2022-11-09
 *********************************************************************/
#pragma once
#include "MProjectNetwork/NetworkDefine.h"
#include <boost/uuid/uuid.hpp>

namespace mproject {
namespace network {

struct FHeader {
protected:
	using UUID = boost::uuids::uuid;
public:
	uint protocol;
	UUID uuid;

	static uint constexpr Protocol_ID = 1;

	FHeader() : protocol(Protocol_ID), uuid(boost::uuids::nil_uuid()) {}
	FHeader(UUID _uuid) : protocol(Protocol_ID), uuid(_uuid) {}
};


template<typename Header = FHeader>
	requires std::derived_from<Header, FHeader>
class Packet {
	Header header;
	std::vector<byte> buffer;

public:

	Packet(std::vector<byte> _buffer) {
		if (_buffer.size() < sizeof(Header)) {
			throw std::runtime_error("Packet buffer is too small.");
		}
		
		header = *reinterpret_cast<Header*>(_buffer.data());
		if (header.protocol != Header::Protocol_ID) {
			throw std::runtime_error("Packet protocol is not correct.");
		}

		buffer = std::vector<byte>(_buffer.begin() + sizeof(Header), _buffer.end());
	}

	Header const& GetHeader() const {
		return header;
	}
	
	std::vector<byte> const& GetBuffer() const {
		return buffer;
	}
};

namespace packet_message {
using type = uint;
type constexpr KEEP_ALIVE_TYPE = 424967295;
type constexpr CONNECTION_TYPE = 424967296;
type constexpr DISCONNECTION_TYPE = 424967297;
}

template<typename Header = FHeader>
	requires std::derived_from<Header, FHeader>
struct PacketMessage {
protected:
	using UUID = boost::uuids::uuid;
public:
	Header header;
	packet_message::type message;

	PacketMessage(UUID _uuid, const packet_message::type _message_type) : header(_uuid), message(_message_type) {}
};

}	// network
}	// mproject
