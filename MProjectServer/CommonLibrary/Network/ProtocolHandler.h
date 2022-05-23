#pragma once
#include "NetworkDefine.h"
#include "BaseProtocol.h"

struct FPacket;
struct FSession;

class BaseHandler {
public:
	virtual void ReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) = 0;
	virtual std::vector<byte> GetHashCode() const = 0;
	virtual std::string GetHashCodeString() const = 0;
	virtual uint GetPacketTag() const = 0;
};

template<typename Protocol = BaseProtocol>
class TProtocolHandler : public BaseHandler {
public:
	TProtocolHandler() : protocol(new Protocol) { ; }

	virtual void ReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) override {
		OnReceivePacket(_session_key, std::move(_packet));
	}

	std::vector<byte> GetHashCode() const override {
		return protocol->GetHashCode();
	}

	std::string GetHashCodeString() const override {
		return protocol->GetHashCodeString();
	}

	virtual uint GetPacketTag() const override {
		return protocol->GetPacketTag();
	}

protected:
	virtual void OnReceivePacket(SessionKey _session_key, std::unique_ptr<FPacket> _packet) { ; }

protected:
	std::unique_ptr<Protocol> protocol;
};

class ProtocolHandlerManager {
	template<typename T>
	using HandlerMap = std::map<T, std::shared_ptr<BaseHandler>>;
	
public:
	virtual void OnRegisterHandler() = 0;
	virtual void ReceivePacket(std::shared_ptr<FSession> _session, std::unique_ptr<FPacket> _packet);
	
	std::unique_ptr<FPacket> CreateProtocolMessage(std::vector<uint> _tags);

protected:
	void RegisterHandler(std::shared_ptr<BaseHandler> _protocol) {
		handler_map.emplace(_protocol->GetHashCodeString(), _protocol);
		handler_tag_map.emplace(_protocol->GetPacketTag(), _protocol);
	}

	void UnregsiterHandler(std::string _hash_code) {
		if (false == handler_map.contains(_hash_code)) {
			return; // error
		}
		auto handler = handler_map[_hash_code];
		handler_map.erase(_hash_code);
		handler_tag_map.erase(handler->GetPacketTag());
	}

	void UnregisterHandler(uint _tag) {
		if (false == handler_tag_map.contains(_tag)) {
			return; // error
		}
		auto handler = handler_tag_map[_tag];
		handler_map.erase(handler->GetHashCodeString());
		handler_tag_map.erase(_tag);
	}

private:
	HandlerMap<std::string> handler_map;
	HandlerMap<uint> handler_tag_map;
};

