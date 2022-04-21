#pragma once
#include "NetworkDefine.h"

class BaseHandler {
public:
	virtual bool ReceivePacket(SessionKey _session_key) { ; }
	std::string GetPacketName() {
		return std::string(typeid(this).name());
	}
};

template<typename Event>
class TProtocolHandler final : public BaseHandler {
public:
	virtual bool ReceivePacket(SessionKey _session_key) override {
		Event data;
		// create data
		OnReceivePacket(data, _session_key);
		return true;
	}

	virtual std::wstring_view GetPacketName() override {
		Event data;
		return data.GetName();
	}
	
private:
	void OnReceivePacket(Event const &_type ,SessionKey _session_key) = 0;
};

class ProtocolHandlerManager {
	using HandlerMap = std::unordered_map<udecimal, std::unique_ptr<BaseHandler>>;
	
public:
	virtual void OnRegisterHandler() = 0;
	virtual void SendPacket();
	virtual void ReceivePacket();

protected:
	template<typename Event>
	void RegisterHandler() {
		if (false == handler_map.try_emplace(Event.HashCode(), std::make_unique<TProtocolHandler<Event>>())) {
			return;
		}
	}

	template<typename Event>
	void UnregsiterHandler() {
		handler_map.erase(Event.HashCode());
	}

private:
	HandlerMap handler_map;
};

