#pragma once
#include <coroutine>
#include <mcs/networking/impl/tcp_client.hpp>
#include <mcs/logger.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/io_context.hpp>
#include <asio/co_spawn.hpp>
#include <asio/awaitable.hpp>
#include <asio/detached.hpp>
#include <asio/signal_set.hpp>
#include <asio/use_awaitable.hpp>

#include <thread>

struct TcpListener
{
public:
    TcpListener(unsigned short port, mcs::modules::Logger* logger)
        : m_IoContext(std::thread::hardware_concurrency()), m_Logger(logger)
    {
        logger->info(std::format("Starting TcpListener on port {}", port));

        try
        {
            co_spawn(m_IoContext, listen(
                asio::ip::tcp::acceptor(m_IoContext, { asio::ip::tcp::v4(), port })
            ), asio::detached);
    
            asio::signal_set signals(m_IoContext, SIGINT, SIGTERM);
            signals.async_wait([&](auto, auto) { m_IoContext.stop(); });

            m_IoContext.run();
        }
        catch(std::exception& e)
        {
            logger->critical(std::format("Exception occured: {}", e.what()));
        }
    }

    asio::awaitable<void> listen(asio::ip::tcp::acceptor acceptor)
    {
        for(;;)
        {
            try
            {
                auto client = std::make_shared<mcs::TcpClient>(
                    co_await acceptor.async_accept(asio::use_awaitable),
                    m_Logger
                );

                m_Logger->info("New client!");
                m_Clients.push_back(client);
            }
            catch (std::exception& e)
            {
                m_Logger->error(std::format("Error: {}", e.what()));
            }
        }
    }

private:
    std::vector<std::shared_ptr<mcs::TcpClient>> m_Clients;
    mcs::modules::Logger* m_Logger;
    asio::io_context m_IoContext;
};