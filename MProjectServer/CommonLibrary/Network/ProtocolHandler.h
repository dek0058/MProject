#pragma once
#include "NetworkDefine.h"
#include "BaseProtocol.h"

struct FPacket;
struct FSession;

class BaseHandler {
public:
	virtual bool ReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) = 0;
	virtual std::string GetPacketName() = 0;
};

template<typename Protocol = BaseProtocol>
class TProtocolHandler final : public BaseHandler {
	TProtocolHandler() : protocol(new Protocol)  { ; }

public:
	virtual bool ReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) override {
		// create data
		OnReceivePacket(data, _session_key);
		return true;
	}

	virtual std::string GetPacketName() override {
		return Protocol::GetHashCodeString();
	}

private:
	void OnReceivePacket(Event const &_type ,SessionKey _session_key) = 0;

protected:
	std::unique_ptr<Protocol> protocol;
};

class ProtocolHandlerManager {
	using HandlerMap = std::map<std::string, std::unique_ptr<BaseHandler>>;
	
public:
	virtual void OnRegisterHandler() = 0;
	virtual void SendPacket(SessionKey _session_key, FPacket* _protocol);
	virtual void ReceivePacket(std::shared_ptr<FSession> _session, std::unique_ptr<FPacket> _packet);

protected:
	template<typename Event>
	void RegisterHandler() {
		if (false == handler_map.try_emplace(Event::GetHashCodeString(), std::make_unique<TProtocolHandler<Event>>())) {
			return;
		}
	}

	template<typename Event>
	void UnregsiterHandler() {
		handler_map.erase(Event::GetHashCodeString());
	}

private:
	HandlerMap handler_map;
};

