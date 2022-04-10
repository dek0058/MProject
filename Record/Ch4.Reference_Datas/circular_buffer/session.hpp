#pragma once

#include "types.hpp"

class session : public std::enable_shared_from_this<session>
{
public:

    session(tcp::socket&& socket)
    : socket(std::move(socket))
    {
    }

    void start()
    {
        // To start an echo session we should start to receive incoming data
        read();
    }

private:

    void read()
    {
        // Schedule asynchronous receiving of a data
        io::async_read(socket, make_view(buffer), io::transfer_at_least(1), std::bind(&session::on_read, shared_from_this(), _1, _2));
    }

    void on_read(error_code error, std::size_t bytes_transferred)
    {
        // Check if an error has occurred or circular buffer is full
        if(!error && bytes_transferred)
        {
            // Check if the session isn't currently writing data
            if(!writing)
            {
                write();
            }

            // Read the next portion of the data
            read();
        }
        else
        {
            close();
        }
    }

    void write()
    {
        writing = true;
        // Schedule asynchronous sending of the data
        io::async_write(socket, make_view(buffer), std::bind(&session::on_write, shared_from_this(), _1, _2));
    }

    void on_write(error_code error, std::size_t bytes_transferred)
    {
        writing = false;

        if(!error)
        {
            // Check if there is something to send it back to the client
            if(buffer.size())
            {
                write();
            }
        }
        else
        {
            close();
        }
    }

    void close()
    {
        error_code error;
        socket.close(error);
    }

    tcp::socket socket;
    bool writing = false;
    circular_buffer<65536> buffer;
};