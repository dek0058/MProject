#pragma once
#include "MWorld.h"


class LoginWorld : public MWorld {
	
public:

	LoginWorld(uint _key);
	
protected:
	
	virtual void OnJoinUser(std::shared_ptr<MUser> _user) override;
	virtual void OnLeftUser(std::shared_ptr<MUser> _user) override;

};
	