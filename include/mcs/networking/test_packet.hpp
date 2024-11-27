#pragma once

#include <asio.hpp>
#include <iostream>

namespace mcs::test
{
    struct Packet
    {
        unsigned long id;
        unsigned long long data_size;
        char* data;

        Packet() = default;

        Packet(unsigned long id, char* data, unsigned long long data_size)
        {
            this->id = id;
            this->data_size = data_size;
            this->data = data;
        }

        static asio::awaitable<size_t> sendPacket(asio::ip::tcp::socket& socket, Packet& packet)
        {
            try 
            {
                std::cout << "sending packet!" << std::endl;
                unsigned char* data = new unsigned char[8];

                memcpy(data, &packet.id, sizeof(packet.id));
                size_t wroteBytes = co_await asio::async_write(socket, asio::buffer(data, sizeof(packet.id)), asio::use_awaitable);

                memcpy(data, &packet.data_size, sizeof(packet.data_size));
                wroteBytes += co_await asio::async_write(socket, asio::buffer(data, sizeof(packet.data_size)), asio::use_awaitable);
                wroteBytes += co_await asio::async_write(socket, asio::buffer(packet.data, packet.data_size), asio::use_awaitable);

                delete[] data;
                std::cout << "wrote: " << wroteBytes << " bytes" << std::endl;
                co_return wroteBytes;
            }
            catch (std::exception& ec)
            {
                std::cerr << ec.what() << std::endl;
            }
        }

        static asio::awaitable<Packet> receivePacket(asio::ip::tcp::socket& socket)
        {
            try
            {
                Packet p{};
                unsigned char* data = new unsigned char[8];

                size_t readBytes = co_await asio::async_read(socket, asio::buffer(data, sizeof(Packet::id)), asio::use_awaitable);
                p.id = *reinterpret_cast<decltype(Packet::id)*>(data);

                readBytes += co_await asio::async_read(socket, asio::buffer(data, sizeof(Packet::data_size)), asio::use_awaitable);
                p.data_size = *reinterpret_cast<decltype(Packet::data_size)*>(data);

                delete[] data;
                char* packet_data = new char[p.data_size];

                readBytes += co_await asio::async_read(socket, asio::buffer(packet_data, p.data_size), asio::use_awaitable);
                p.data = packet_data;
                co_return p;
            } 
            catch (std::exception& ec)
            {
                std::cerr << ec.what() << std::endl;
            }
        }
    };
}