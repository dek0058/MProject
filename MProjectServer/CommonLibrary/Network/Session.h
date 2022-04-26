#pragma once
#include <boost/asio.hpp>
#include <boost/circular_buffer.hpp>

#include "NetworkDefine.h"
#include "Utility/CircularBuffer.h"
#include "Utility//MemoryPool.h"

class IOService;

struct FSession : public std::enable_shared_from_this<FSession> {
	friend class NetworkServer;
	friend class IOService;
	friend class IOAcceptor;
	friend class IOConnector;

public:
	FSession(std::shared_ptr<IOService> _IO_service, ESessionType _session_type, size_t _send_buffer_size, size_t _recv_buffer_size, int _max_packet_size);
	~FSession();


	// getter
	SessionKey GetSessionKey() const {
		return session_key;
	}
	
	ESessionType GetSessionType() const {
		return session_type;
	}

	ESequenceType GetSequenceType() const {
		return sequence_type;
	}

	std::wstring GetPublicIP() const {
		return std::format(L"{}:{}", public_ip, public_port);
	}

	ushort GetPublicPort() const {
		return public_port;
	}

	bool IsWriting() const {
		return is_writing.load();
	}

	size_t ReceiveBufferSize() const {
		return recv_buffers.UsedSize();
	}

	// setter
	void SetSequenceType(ESequenceType _type) {
		sequence_type = _type;
	}
	
	void SetPublicIP(std::wstring const& _ip, ushort const& _port) {
		public_ip = _ip;
		public_port = _port;
	}
	
	void SetWriting(bool _value) {
		is_writing.store(_value);
	}

private:
	void Accept(SessionKey _session_key);
	void Connect(SessionKey _session_key);
	void Disconnect();
	void Shutdown();
	void Close();

	void Receive();
	void Write(size_t _size);

	void OnReceive(boost::system::error_code const& _error_code, size_t _bytes_transferred);
	void OnWrite(boost::system::error_code const& _error_code, size_t _bytes_transferred);
	void OnDisconnect();

	void Flush();

	boost::asio::ip::tcp::socket& GetSocket() { return sock; }

private:

	std::shared_ptr<IOService> top_IO_service;

	boost::asio::ip::tcp::socket sock;
	boost::asio::io_service::strand strand;

	/// information
	SessionKey session_key;
	ESessionType session_type;
	ESequenceType sequence_type;
	std::wstring public_ip;
	ushort public_port;

	/// buffer
	MemoryPool<byte[PACKET_MEMORY_POOL_SIZE]> buffer_pool;
	byte* send_buffer;
	byte* recv_buffer;
	CircularBuffer_M send_buffers;
	CircularBuffer_M recv_buffers;

	int max_packet_size;
	std::atomic<bool> is_writing;
};