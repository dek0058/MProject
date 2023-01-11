/*****************************************************************//**
 * \file   Socket.h
 * \brief  reliable udp socket
 *
 * \author dek0058
 * \date   2022-11-09
 *********************************************************************/
#pragma once
#include "MProjectNetwork/NetworkDefine.h"
#include "MProjectLogger/Core/ILogger.h"
#include "Peer.h"
#include "Packet.h"
#include "Utility/CircularBuffer.h"

namespace mproject {
namespace network {

class MEngine;
class IOService;

template<typename Header = FHeader>
	requires std::derived_from<Header, FHeader>
class Socket {
	using UDP_Scoket = UDP::socket;
private:
	template<typename... Types>
	using HandlerType = std::function<void(Types...)>;
	using ReceiveHandlerType = HandlerType<Packet<Header> const&, size_t, FPeer const&>;
	using ConnectionHandlerType = HandlerType<FPeer const&>;
	using DisconnectionHandlerType = HandlerType<FPeer const&>;
	using TimeoutHandlerType = HandlerType<FPeer const&>;

public:

	/** Construct accept cocket*/
	Socket(
		boost::asio::io_service& _IO_service,
		EndPoint _endpoint,
		size_t _receive_packet_capacity,
		size_t _max_packet_size,
		decimal _heartbeat_second,
		std::shared_ptr<logger::ILogger> _logger
	)
		: IO_service(_IO_service)
		, socket(_IO_service)
		, strand(_IO_service)
		, timer(_IO_service)
		, self(_endpoint)
		, receive_packet_capacity(_receive_packet_capacity)
		, max_packet_size(_max_packet_size)
		, listening(false)
		, remote_endpoint(_endpoint)
		, sync_buffer(_receive_packet_capacity)
		, heartbeat_second(_heartbeat_second)
		, logger(_logger)
	{
		receive_buffer.resize(receive_packet_capacity);
	}

	/** Construct connect socket*/
	Socket(
		boost::asio::io_service& _IO_service,
		size_t _receive_packet_capacity,
		size_t _max_packet_size,
		decimal _heartbeat_second,
		std::shared_ptr<logger::ILogger> _logger
	)
		: IO_service(_IO_service)
		, socket(_IO_service)
		, strand(_IO_service)
		, timer(_IO_service)
		, self(EndPoint(boost::asio::ip::address_v6::loopback(), 0))
		, receive_packet_capacity(_receive_packet_capacity)
		, max_packet_size(_max_packet_size)
		, listening(false)
		, sync_buffer(_receive_packet_capacity)
		, heartbeat_second(_heartbeat_second)
		, logger(_logger)
	{
		receive_buffer.resize(receive_packet_capacity);
	}

public:

	void Start() {
		listening = true;
		HeartBeat();
		Receive();
	}

	void Open() {
		socket.open(remote_endpoint.protocol());
	}

	void Close() noexcept {
		PacketMessage<Header> message(Self().uuid, packet_message::DISCONNECTION_TYPE);
		AsyncSendToAll(reinterpret_cast<void*>(&message), sizeof(message));

		listening = false;
	}

	void Connect(EndPoint& _endpoint) {
		remote_endpoint = _endpoint;
		Open();

		PacketMessage<Header> message(Self().uuid, packet_message::CONNECTION_TYPE);
		AsyncSendTo(reinterpret_cast<void*>(&message), sizeof(message), remote_endpoint);

		listening = true;

		Start();
	}

	void Bind() noexcept {
		socket.bind(remote_endpoint);
	}

	void AsyncSendTo(void* _buffer, size_t _buffer_size, EndPoint& _end_point) {
		socket.async_send_to(
			boost::asio::buffer(_buffer, _buffer_size),
			_end_point,
			boost::asio::bind_executor(
				strand,
				[this](boost::system::error_code const& _error, size_t _bytes_transferred) {
					if (_error != boost::system::errc::success) {
						if (logger != nullptr) {
							logger->WriteLog(logger::ELogLevel::Error, FString(_error.message()));
						}
					}
				}
			)
		);
	}

	void AsyncSendToAll(void* _buffer, size_t _buffer_size) {
		for (auto& peer : peers) {
			AsyncSendTo(_buffer, _buffer_size, peer.endpoint);
		}
	}

	FPeer const& Self() const {
		return self;
	}

	void SetReceiveHandler(ReceiveHandlerType const& _handler) {
		receive_handler = _handler;
	}

	void SetConnectionHandler(ConnectionHandlerType const& _handler) {
		connection_handler = _handler;
	}

	void SetDisconnectionHandler(DisconnectionHandlerType const& _handler) {
		disconnection_handler = _handler;
	}

	void SetTimeoutHandler(TimeoutHandlerType const& _handler) {
		timeout_handler = _handler;
	}

private:

	void OnRecive(boost::system::error_code const& _error_code, size_t _bytes_transferred) {
		try {
			if (_error_code) {
				throw boost::system::system_error(_error_code);
			}

			if (max_packet_size < _bytes_transferred) {
				throw std::exception(std::format("Packet is too large... Packet:{} MaxPacket:{}", _bytes_transferred, max_packet_size).c_str());
			}

			Packet<Header> packet(std::vector<byte>(receive_buffer.begin(), receive_buffer.begin() + _bytes_transferred));

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
				packet_message::type message = *reinterpret_cast<packet_message::type const*>(packet.GetBuffer().data());

				if (message == packet_message::CONNECTION_TYPE || message == packet_message::KEEP_ALIVE_TYPE) {
					is_a_user_message = false;
				} else if(message == packet_message::DISCONNECTION_TYPE) {
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
		} catch (std::exception _e) {
			if (logger != nullptr) {
				logger->WriteLog(logger::ELogLevel::Error, FString(_e.what()));
			}
		} catch (...) {
		}

		if (listening) {
			Receive();
		}
	}
	
	void Receive() {
		socket.async_receive_from(
			boost::asio::buffer(receive_buffer.data(), receive_packet_capacity),
			remote_endpoint,
			boost::asio::bind_executor(
				strand,
				[this](auto _error_code, auto _bytes_transferred) {
					OnRecive(_error_code, _bytes_transferred);
				}
			)
		);
	}

	void OnHeartBeat() {
		std::chrono::seconds now = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
		std::chrono::seconds timeout = std::chrono::seconds(heartbeat_second);

		peers.erase(
			std::remove_if(peers.begin(), peers.end(), [this, &now, &timeout](FPeer const& _peer) -> bool {
				if (_peer.last_packet_timestamp + timeout < now) {
					if (timeout_handler) {
						timeout_handler(_peer);
					}
					return true;
				}
				return false;
			}),
			peers.end()
		);

		if (listening) {
			PacketMessage<Header> message(Self().uuid, packet_message::KEEP_ALIVE_TYPE);
			AsyncSendToAll(reinterpret_cast<void*>(&message), sizeof(message));
			HeartBeat();
		}
	}
	
	void HeartBeat() {
		timer->expires_from_now(boost::posix_time::seconds(heartbeat_second));
		timer->async_wait([this](boost::system::error_code const& _error_code) {
			if (_error_code != boost::system::errc::success) {
				// TODO:연결 끊기
				return;
			}
			OnHeartBeat();
		});
	}
public:

	size_t receive_packet_capacity;
	size_t max_packet_size;
	decimal heartbeat_second;
	bool listening;
	
	boost::asio::io_service& IO_service;
	UDP_Scoket socket;
	boost::asio::io_service::strand strand;
	EndPoint remote_endpoint;
	std::optional<boost::asio::deadline_timer> timer;

	FPeer self;
	CircularBuffer_A sync_buffer;
	std::vector<byte> receive_buffer;
	std::vector<FPeer> peers;

	ReceiveHandlerType receive_handler;
	ConnectionHandlerType connection_handler;
	DisconnectionHandlerType disconnection_handler;
	TimeoutHandlerType timeout_handler;

	std::shared_ptr<logger::ILogger> logger;
};

}	// network
}	// mproject

