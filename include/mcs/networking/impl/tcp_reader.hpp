#pragma once
#include <mcs/networking/impl/socket_holder.hpp>
#include <mcs/networking/impl/timer_holder.hpp>
#include <mcs/protocol/data_types.hpp>
#include <mcs/networking/test_packet.hpp>
#include <asio/awaitable.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/read.hpp>
#include <asio/use_awaitable.hpp>
#include <asio/buffer.hpp>

#include <iostream>
#include <functional>
#include <memory>
#include <vector>

namespace mcs
{
    constexpr size_t MAX_BUFFER_SIZE = 1000000;
    using handle_data_t = std::function<asio::awaitable<size_t>(mcs::test::Packet packet)>;

    struct TcpReader : public std::enable_shared_from_this<TcpReader>, std::shared_ptr<TcpReader>
    {
    public:
        static std::shared_ptr<TcpReader> make_shared(SocketHolder& socket)
        {
            return std::shared_ptr<TcpReader>(new TcpReader(socket));
        }

        ~TcpReader()
        {
            stop();
        }

        asio::awaitable<void> read(handle_data_t handler)
        {
            try
            {
                std::vector<mcs_byte> data;
                for(;;)
                {
                    auto packet = co_await mcs::test::Packet::receivePacket(m_Socket.get());

                    size_t n = co_await handler(packet);
                    std::cout << "Handled: " << n << "bytes" << std::endl;
                }

                stop();
            } 
            catch(std::exception&)
            {
                stop();
            }
        }

        void start(handle_data_t handler_function)
        {
            asio::co_spawn(m_Socket.get().get_executor(), [handler_function, self = shared_from_this()] {
                return self->read(handler_function);
            }, asio::detached);
        }
    protected:
        TcpReader(SocketHolder& socket)
            : m_Socket(socket), m_Timer(socket.get().get_executor())
        {
        }

        

        void stop()
        {
            m_Socket.get().close();
            m_Timer.cancel();
        }

    private:    
        SocketHolder& m_Socket;
        TimerHolder<asio::steady_timer> m_Timer;
        std::vector<mcs_byte> m_Data;
    };
} // namespace mcs
