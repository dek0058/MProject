#pragma once
#include "MWorld.h"


class LoginWorld : public MWorld {
	
public:

	LoginWorld(uint _key);
	
protected:
	
	virtual void OnJoinUser(std::weak_ptr<MUser> _user) override;
	virtual void OnLeftUser(std::weak_ptr<MUser> _user) override;

};
	