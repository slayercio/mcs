#pragma once
#include <asio/ip/tcp.hpp>

namespace mcs
{
    struct SocketHolder
    {
    public:
        SocketHolder(asio::ip::tcp::socket socket)
            : m_Socket(std::move(socket))
        {
        }
        
        asio::ip::tcp::socket& get()
        {
            return m_Socket;
        }

    private:
        asio::ip::tcp::socket m_Socket;
    };
}