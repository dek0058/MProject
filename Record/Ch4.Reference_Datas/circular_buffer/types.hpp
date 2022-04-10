#include <iostream>
#include <optional>
#include <boost/asio.hpp>
#include <boost/container/static_vector.hpp>
#include <boost/lexical_cast.hpp>

namespace io = boost::asio;
namespace ip = io::ip;
using tcp = ip::tcp;
using error_code = boost::system::error_code;
using namespace std::placeholders;