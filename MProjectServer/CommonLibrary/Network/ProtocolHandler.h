#pragma once
#include "NetworkDefine.h"
#include "BaseProtocol.h"

struct FPacket;
struct FSession;

class BaseHandler {
public:
	virtual void ReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) = 0;
};

template<typename Protocol = BaseProtocol>
class TProtocolHandler : public BaseHandler {
	TProtocolHandler() : protocol(new Protocol)  { ; }

public:
	virtual void ReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) override {
		OnReceivePacket(_session_key, std::move(_packet));
	}

protected:
	virtual void OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) = 0;

protected:
	std::unique_ptr<Protocol> protocol;
};

class ProtocolHandlerManager {
	using HandlerMap = std::map<std::string, std::unique_ptr<BaseHandler>>;
	
public:
	virtual void OnRegisterHandler() = 0;
	virtual void ReceivePacket(std::shared_ptr<FSession> _session, std::unique_ptr<FPacket> _packet);

protected:
	template<typename Protocol = BaseProtocol, typename Handler = TProtocolHandler<Protocol>>
	void RegisterHandler() {
		handler_map.emplace(Protocol::GetHashCodeString(), std::unique_ptr<Handler>());
	}

	template<typename Protocol = BaseProtocol>
	void UnregsiterHandler() {
		handler_map.erase(Protocol::GetHashCodeString());
	}

private:
	HandlerMap handler_map;
};

