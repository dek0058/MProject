#pragma once
#include <boost/asio.hpp>
#include <boost/circular_buffer.hpp>

#include "NetworkDefine.h"
#include "Utility/CircularBuffer.h"


class IOService;

struct FSession : public std::enable_shared_from_this<FSession> {

public:
	FSession(std::shared_ptr<IOService> _IO_service, ESessionType _session_type, size_t _send_buffer_size, size_t _recv_buffer_size, int _max_packet_size);
	~FSession();

	// getter
	SessionKey GetSessionKey() {
		return session_key;
	}

	ESessionType GetSessionType() {
		return session_type;
	}

	ESequenceType GetSequenceType() {
		return sequence_type;
	}

	bool IsWriting() {
		return is_writing.load();
	}

	// setter
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
	void Write(char* const _data, size_t _size, std::wstring const* _name);

	void OnReceive(boost::system::error_code const& _error_code, size_t _bytes_transferred);
	void OnWrite(boost::system::error_code const& _error_code, size_t _bytes_transferred);

	void OnDisconnect();

	boost::asio::ip::tcp::socket& GetSocket() { return sock; }

private:

	std::shared_ptr<IOService> top_IO_service;

	boost::asio::ip::tcp::socket sock;
	boost::asio::io_service::strand strand;


	/// information
	SessionKey session_key;
	ESessionType session_type;

	ESequenceType sequence_type;

	std::vector<boost::asio::const_buffer> send_buffer;
	std::vector<boost::asio::mutable_buffer> recv_buffer;
	CircularBuffer_M send_buffers;
	CircularBuffer_M recv_buffers;

	int max_packet_size;
	std::atomic<bool> is_writing;
};