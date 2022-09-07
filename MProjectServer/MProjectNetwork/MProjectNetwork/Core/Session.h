#pragma once

//! library
#include <boost/asio.hpp>

#include "MProjectNetwork/NetworkDefine.h"
#include "Core/MObject.h"

namespace mproject {
namespace network {

class IOService;
class SessionPool;

class Session : public MObject, public std::enable_shared_from_this<Session> {
	
public:
	Session(std::shared_ptr<IOService> _IO_service, ESessionType _session_type);
	~Session();

public:
	virtual void Accept() = 0;
	virtual void Disconnect() = 0;
	virtual void Shutdown() = 0;
	virtual void Close() = 0;
	
public: //! Setter
	void SetParent(std::weak_ptr<SessionPool> _session_pool);

public: //! Getter
	std::weak_ptr<IOService> GetIOService() {
		return IO_Service;
	}

	SessionKey GetSessionKey() const {
		return session_key;
	}

	ESessionType GetSessionType() const {
		return session_type;
	}

	ESequenceType GetSequenceType() const {
		return sequence_type;
	}

protected:
	//! parent
	std::weak_ptr<SessionPool> session_pool;

	//! network
	std::shared_ptr<IOService> IO_Service;

	//! information
	SessionKey session_key;
	ESessionType session_type;
	ESequenceType sequence_type;
};

class Session_TCP : public Session {

public:
	Session_TCP(std::shared_ptr<IOService> _IO_service, ESessionType _session_type);
	~Session_TCP();
	
public:

	/// <summary>연결된 세션에 접속을 알립니다.</summary>
	virtual void Accept() override;
	
	/// <summary>연결된 세션에 접속 해제를 알립니다.</summary>
	virtual void Disconnect() override;
	
	/// <summary>세션을 강제 종료합니다.</summary>
	void Shutdown();
	
	/// <summary>세션을 종료합니다.</summary>
	void Close();

public: //! Getter
	boost::asio::ip::tcp::socket& GetSocket() {
		return sock;
	}

	std::weak_ptr<IOService> GetIOService() {
		return IO_Service;
	}
	
	SessionKey GetSessionKey() const {
		return session_key;
	}

	ESessionType GetSessionType() const {
		return session_type;
	}

	ESequenceType GetSequenceType() const {
		return sequence_type;
	}

private:

	//! network
	boost::asio::ip::tcp::socket sock;
	boost::asio::io_service::strand strand;
	
};


}	// network
}	// mproject
