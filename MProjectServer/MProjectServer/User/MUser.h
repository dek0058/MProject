#pragma once
#include "Network/NetworkDefine.h"

struct FSession;

class MUser {
	

	// 테스트 유저 키 발급 (원래는 DB에서 발급해야하는 키값임)
	static uint GetTestUserKey() {
		static uint key = 0;
		return ++key;
	}

public:

	MUser(std::shared_ptr<FSession> _session);
	~MUser();

	uint SessionKey() const;
	uint GetUserKey() const;
	

private:

	std::shared_ptr<FSession> session;
	uint user_key;

};