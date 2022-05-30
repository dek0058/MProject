#pragma once
#include "MWorld.h"

class TestWorld : public MWorld {
	
public:

	TestWorld(uint _key);
	
protected:

	virtual void OnJoinUser(std::weak_ptr<MUser> _user) override;
	virtual void OnLeftUser(std::weak_ptr<MUser> _user) override;
};
