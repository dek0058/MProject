#pragma once
#include <boost/asio.hpp>
#include <boost/circular_buffer.hpp>

#include "NetworkDefine.h"

using namespace boost;

class IOService;

struct FSession {

public:
	FSession(shared_ptr<IOService> _IO_service, ESessionType _session_type, size_t _send_buffer_size, size_t _recv_buffer_size);
	~FSession();

	// getter
	SessionKey GetSessionKey() {
		return session_key;
	}

	ESessionType GetSessionType() {
		return session_type;
	}

private:
	void Accept(SessionKey _session_key);
	void Connect();
	void Disconnect();


	asio::ip::tcp::socket& GetSocket() { return sock; }

private:

	asio::ip::tcp::socket sock;
	asio::io_service::strand strand;


	/// information
	SessionKey session_key;
	ESessionType session_type;

	ESequenceType sequence_type;

	circular_buffer<char> send_buffers;
	circular_buffer<char> recv_buffers;
};