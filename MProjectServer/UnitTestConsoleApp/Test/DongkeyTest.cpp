#include "DongkeyTest.h"
#include "UnitTestSuite.h"
#include "UnitTestCaller.h"

#include <iostream>
#include <string>
#include <map>

#include <boost/asio.hpp>

DongkeyTest::DongkeyTest(std::string const& _name) : UnitTestCase(_name) {
}

DongkeyTest::~DongkeyTest() {
}

void DongkeyTest::TestMap() {
	
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket socket(io_service);
	
	boost::asio::ip::address address = boost::asio::ip::address::from_string("127.0.0.1");
	boost::asio::ip::tcp::endpoint end_point(address, 3333);

	socket.open(end_point.protocol());
	
	socket.async_connect(end_point, [this](boost::system::error_code const& _error_code) {
		if (_error_code != boost::system::errc::success) {
			return;
		}



	});
}

UnitTest* DongkeyTest::Suite() {
	UnitTestSuite* suite = new UnitTestSuite("DongkeyTest");
	TUnitTest_AddTest(suite, DongkeyTest, TestMap);
	return suite;
}

