/*****************************************************************//**
 * \file   IOService.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-10-04
 * \version 0.1
 *********************************************************************/

#pragma once
#include "MProjectNetwork/NetworkDefine.h"

#include <boost/asio/io_service.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/thread/thread.hpp>

namespace mproject {
namespace network {

class IOService : std::enable_shared_from_this<IOService> {

public:
	IOService();
	~IOService();
	
public:
	
	/**
	 * \brief runnable io serive
	 */
	void Run();

	/**
	 * \brief stop io service
	 */
	void Stop();

	/**
	 * \brief request io service to stop
	 */
	void RequestStop();

	/**
	 * \return IOService instance
	 */
	boost::asio::io_service& Get() {
		return data;
	}

private:
	boost::asio::io_service data;
	std::stop_source stop_source;
	std::vector<std::jthread> IO_thread_group;
};

}	// network
}	// mproject

