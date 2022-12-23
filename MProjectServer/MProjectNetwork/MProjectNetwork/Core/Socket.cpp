#include "Socket.h"
#include "MProjectNetwork/Core/IOService.h"
#include "MProjectNetwork/Server/MEngine.h"
#include "Exception/ExceptionUtility.h"

namespace mproject {
namespace network {

template <typename Header>
	requires std::derived_from<Header, FHeader>
Socket<Header>::Socket(
	boost::asio::io_service& _IO_service,
	EndPoint _endpoint,
	size_t _receive_packet_capacity,
	size_t _max_packet_size,
	uint _heartbeat_second /* = 5*/)
	: socket(_IO_service)
	, strand(_IO_service)
	, timer(_IO_service)
	, self(_endpoint)
	, receive_packet_capacity(_receive_packet_capacity)
	, max_packet_size(_max_packet_size)
	, listening(true)
	, remote_endpoint(_endpoint)
	, sync_buffer(receive_packet_capacity)
	, heartbeat_second(_heartbeat_second) {

	receive_buffer.reserve(max_packet_size);

	HeartBeat();
	Receive();
}

template <typename Header>
	requires std::derived_from<Header, FHeader>
void Socket<Header>::Close() noexcept {
	PacketMessage<Header> message(Self().uuid, packet_message::DISCONNECTION_TYPE);
	AsyncSendToAll(reinterpret_cast<void*>(&message), sizeof(message));

	listening = false;
}

template <typename Header>
	requires std::derived_from<Header, FHeader>
void Socket<Header>::Connect(EndPoint& _endpoint) {
	socket->open(remote_endpoint->protocol());
	
	PacketMessage<Header> message(Self().uuid, packet_message::CONNECTION_TYPE);
	AsyncSendTo(reinterpret_cast<void*>(&message), sizeof(message), remote_endpoint);
	
	listening = true;

	HeartBeat();
	Receive();
}

template <typename Header>
	requires std::derived_from<Header, FHeader>
void Socket<Header>::OnRecive(boost::system::error_code const& _error_code, size_t _bytes_transferred) {
	if (_error_code != boost::system::errc::success) {
		// TODO: 실패... 연결 끊기 시도
		return;
	}
	
	try {
		Packet<Header> packet(receive_buffer);

		std::vector<FPeer>::iterator peer_iter = std::find_if(peers.begin(), peers.end(), [this, &packet](FPeer& _peer) -> bool {
			if (_peer.uuid == packet.GetHeader().uuid) {
				_peer.last_packet_timestamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
				return true;
			}
			return false;
		});

		if (peer_iter == peers.end()) {
			peers.emplace_back(
				remote_endpoint,
				packet.GetHeader().uuid,
				std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch())
			);
			peer_iter = peers.end() - 1;

			if (connection_handler) {
				connection_handler(*peer_iter);
				PacketMessage<Header> message(Self().uuid, packet_message::CONNECTION_TYPE);
				AsyncSendTo(reinterpret_cast<void*>(&message), sizeof(message), peer_iter->endpoint);
			}
		}

		bool is_a_user_message = true;
		if (_bytes_transferred - sizeof(Header) == sizeof(packet_message::type))
		{
			packet_message::type message = *reinterpret_cast<packet_message::type*>(packet.GetBuffer().data());
			if (message == packet_message::CONNECTION_TYPE || message == packet_message::KEEP_ALIVE_TYPE) {
				is_a_user_message = false;
			} else if (message == packet_message::DISCONNECTION_TYPE) {
				is_a_user_message = false;
				if (disconnection_handler) {
					disconnection_handler(*peer_iter);
				}
				
				peers.erase(
					std::remove_if(peers.begin(), peers.end(), [this, &peer_iter](FPeer const& _peer) -> bool {
						return peer_iter->uuid == _peer.uuid;
					}), 
					peers.end()
				);
			}
		}
		
		if (is_a_user_message && receive_handler) {
			receive_handler(packet, _bytes_transferred, *peer_iter);
		}
	}
	catch (std::exception const& _e) {
		// TODO: bad packet
	}

	if (listening) {
		Receive();
	}
}

template <typename Header>
	requires std::derived_from<Header, FHeader>
void Socket<Header>::Receive() {
	socket->async_receive_from(
		boost::asio::buffer(receive_buffer),
		remote_endpoint.value(),
		boost::asio::bind_executor(
			strand.value(),
			[this](boost::system::error_code const& _error_code, size_t _bytes_transferred) {
				OnRecive(_error_code, _bytes_transferred);
			}
		)
	);
}

template <typename Header>
	requires std::derived_from<Header, FHeader>
void Socket<Header>::OnHeartBeat() {
	std::chrono::seconds now = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
	std::chrono::seconds timeout = std::chrono::seconds(heartbeat_second);
	
	peers.erase(
		std::remove_if(peers.begin(), peers.end(), [this, &now, &timeout](FPeer const& _peer) -> bool {
			if (_peer.last_packet_timestamp + timeout < now) {
				if (disconnection_handler) {
					disconnection_handler(_peer);
				}
				return true;
			}
			return false;
		}),
		peers.end()
	);

	if (listening) {
		PacketMessage<Header> message(Self().uuid, packet_message::KEEP_ALIVE_TYPE);
		AsyncSendToAll(reinterpret_cast<void*>(*message), sizeof(message));
		HeartBeat();
	}

}

template <typename Header>
	requires std::derived_from<Header, FHeader>
void Socket<Header>::HeartBeat() {
	timer->expires_from_now(boost::posix_time::seconds(heartbeat_second));
	timer->async_wait([this](boost::system::error_code const& _error_code) {
		if (_error_code != boost::system::errc::success)
		{
			// TODO:연결 끊기
			return;
		}

		OnHeartBeat();
	});
}

}	// network
}	// mproject
