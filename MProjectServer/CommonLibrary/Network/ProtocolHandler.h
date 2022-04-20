#pragma once
#include "NetworkDefine.h"

class BaseHandler {
public:
	virtual bool ReceivedPacket(SessionKey _session_key) = 0;
	virtual std::wstring_view GetPacketName() = 0;
};

template<typename MsgType>
class TProtocolHandler final : public BaseHandler {
public:
	virtual bool ReceivedPacket(SessionKey _session_key) override {
		return false;
	}

	virtual std::wstring_view GetPacketName() {
		return std::wstring();
	}
private:
	void OnReceivedPacket(MsgType const &_type ,SessionKey _session_key) = 0;
};

class ProtocolHandlerManager {
	using HandlerMap = std::unordered_map<udecimal, std::unique_ptr<BaseHandler>>;
	
public:
	virtual void OnRegisterHandler() = 0;

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
