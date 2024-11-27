#include <mcs/core/core.hpp>
#include <mcs/logger.hpp>
#include <mcs/networking/networking.hpp>
#include <mcs/buffer/buffer.hpp>
#include <format>

constexpr int BUFFER_TEST_INT = 0xF12dda;

int main() {
    auto core = mcs::modules::CoreModule(nullptr);
    auto logger = mcs::modules::LoggerModule(core.get());
    auto net = mcs::modules::NetworkingModule(core.get());
    auto buffer = mcs::modules::BufferModule(core.get());

    logger->info("Hello from logger!");
    logger->warn("Hello from logger!");
    logger->critical("Hello from logger!");
    logger->error("Hello from logger!");
    logger->debug("Hello from logger!");

    auto buf = buffer->create_buffer();

    buf->write_int(BUFFER_TEST_INT);
    int x = buf->read_int();
    logger->info(std::format("Wrote {}, got: {}", BUFFER_TEST_INT, x));

    buf->write_varint(BUFFER_TEST_INT & 0xff123);
    x = buf->read_varint();
    logger->info(std::format("Wrote varint {}, got: {}", BUFFER_TEST_INT & 0xff123, x));

    auto server = net->create_server(10000);
}