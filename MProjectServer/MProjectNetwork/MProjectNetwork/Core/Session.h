/*****************************************************************//**
 * \file   Session.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-10-08
 *********************************************************************/

#pragma once
#include "MProjectNetwork/NetworkDefine.h"

#include <boost/asio.hpp>

namespace mproject {
namespace network {


class Session : std::enable_shared_from_this<Session> {
public:
	//Session(std::shared_ptr<MEngine> _server);


private:

	//SessionKey session_key;
	
	//boost::asio::ip::tcp::socket accept_socket;
	
};

}	// network
}	// mproject
