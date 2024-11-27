#pragma once
#include <asio.hpp>
#include <mcs/networking/impl/socket_holder.hpp>
#include <mcs/networking/impl/tcp_reader.hpp>
#include <mcs/logger.hpp>

namespace mcs
{
    struct TcpClient 
    {
    public:
        TcpClient(asio::ip::tcp::socket socket, mcs::modules::Logger* logger)
            : m_Socket(std::move(socket)), m_Logger(logger)
        {
            m_Reader = TcpReader::make_shared(m_Socket);
            m_Reader->start([this](mcs::test::Packet p) {
                return this->handle_data(p);
            });
        }

        asio::awaitable<size_t> handle_data(mcs::test::Packet packet)
        {
            m_Logger->info(std::format("Received packet! id = {}, data_size = {}, data = \"{}\"", packet.id, packet.data_size, std::string(packet.data, packet.data_size)));

            size_t bytesWritten = co_await mcs::test::Packet::sendPacket(m_Socket.get(), packet);
            co_return bytesWritten;
        }
        
    private:
        mcs::modules::Logger*      m_Logger;
        std::shared_ptr<TcpReader> m_Reader;
        SocketHolder               m_Socket;
    };
}