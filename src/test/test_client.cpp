#define _WIN32_WINNT 0x0A00
#include <asio.hpp>
#include <string>
#include <iostream>
#include <mcs/networking/test_packet.hpp>

using namespace asio;
using namespace asio::ip;

asio::awaitable<void> send(tcp::socket& socket)
{
    std::string msg;
    std::cin >> msg;
 
    mcs::test::Packet p(1, msg.data(), msg.size());

    size_t n = co_await mcs::test::Packet::sendPacket(socket, p);
    std::cout << "Wrote packet: " << n << std::endl;

    auto packet = co_await mcs::test::Packet::receivePacket(socket);
    std::cout << "received packet: " << packet.id << ", data_size: " << packet.data_size << std::endl;
    std::cout << std::string(packet.data, packet.data_size) << std::endl;

    // std::string data_received;
    // size_t w = co_await asio::async_write(socket, buffer(msg), use_awaitable);
    // size_t r = co_await asio::async_read(socket, dynamic_buffer(data_received, w), use_awaitable);

    // std::cout << "w: " << w << ", r: " << r << std::endl;
    // std::cout << data_received << std::endl;

    // socket.close();
}

int main()
{
    try 
    {
        io_context io_ctx;

        tcp::resolver resolver(io_ctx);
        auto endpoints = resolver.resolve("127.0.0.1", "10000");
        tcp::socket socket(io_ctx);
        asio::connect(socket, endpoints);
        
        co_spawn(io_ctx, send(socket), asio::detached);
    
        auto work = asio::make_work_guard(io_ctx);
        io_ctx.run();
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}