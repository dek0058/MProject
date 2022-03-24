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
public:
	virtual void OnRegisterHandler() = 0;

protected:


private:
	using HandlerMap = std::map<udecimal, std::unique_ptr<BaseHandler>>;
	HandlerMap handler_map;
};
