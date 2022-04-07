#pragma once
#include <boost/asio.hpp>
//#include <boost/circular_buffer.hpp>

#include "NetworkDefine.h"

using namespace boost;

class IOService;

struct FSession {

public:
	FSession(shared_ptr<IOService> _IO_service, ESessionType _session_type);
	~FSession();

	// getter
	SessionKey GetSessionKey() {
		return session_key;
	}

private:
	asio::ip::tcp::socket& GetSocket() { return sock; }


private:

	asio::ip::tcp::socket sock;
	asio::io_service::strand strand;


	/// information
	SessionKey session_key;
	ESessionType session_type;

	ESequenceType sequence_type;
};