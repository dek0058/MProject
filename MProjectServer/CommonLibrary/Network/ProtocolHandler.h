#pragma once
#include "NetworkDefine.h"
#include "BaseProtocol.h"

struct FPacket;
struct FSession;

class BaseHandler {
public:
	virtual void ReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) = 0;
	virtual std::string GetPacketName() = 0;
};

template<typename Protocol = BaseProtocol>
class TProtocolHandler final : public BaseHandler {
	TProtocolHandler() : protocol(new Protocol)  { ; }

public:
	virtual void ReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) override {
		OnReceivePacket(_session_key, std::move(_packet));
	}

	virtual std::string GetPacketName() override {
		return std::string();
		//return Protocol::GetHashCodeString();
	}

private:
	virtual void OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) = 0;

protected:
	std::unique_ptr<Protocol> protocol;
};

class ProtocolHandlerManager {
	using HandlerMap = std::map<std::string, std::unique_ptr<BaseHandler>>;
	
public:
	virtual void OnRegisterHandler() = 0;
	virtual void SendPacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet);
	virtual void ReceivePacket(std::shared_ptr<FSession> _session, std::unique_ptr<FPacket> _packet);

protected:
	template<typename Protocol = BaseProtocol>
	void RegisterHandler() {
		if (false == handler_map.try_emplace(Protocol::GetHashCodeString(), std::make_unique<TProtocolHandler<Protocol>>())) {
			return;
		}
	}

	template<typename Protocol = BaseProtocol>
	void UnregsiterHandler() {
		handler_map.erase(Protocol::GetHashCodeString());
	}

private:
	HandlerMap handler_map;
};

