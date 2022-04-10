#include "circular_buffer_view.hpp"
#include "session.hpp"

class server
{
public:

    server(io::io_context& io_context, std::uint16_t port)
    : io_context(io_context)
    , acceptor  (io_context, tcp::endpoint(tcp::v4(), port))
    {
        accept();
    }

private:

    void accept()
    {
        socket.emplace(io_context);

        acceptor.async_accept(*socket, [&] (error_code error)
        {
            // Make session object and start it right away
            std::make_shared<session>(std::move(*socket))->start();
            accept();
        });
    }

    io::io_context& io_context;
    tcp::acceptor acceptor;
    std::optional<tcp::socket> socket;
};

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cout << "Usage: server [Port]\n";
        return 0;
    }

    io::io_context io_context;
    server srv(io_context, boost::lexical_cast<std::uint16_t>(argv[1]));
    io_context.run();

    return 0;
}