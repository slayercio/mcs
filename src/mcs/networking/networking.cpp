#define _WIN32_WINNT 0x0A00

#include <mcs/common/module.hpp>
#include <mcs/networking/networking.hpp>
#include <mcs/networking/impl/tcp_listener.hpp>
#include <mcs/logger.hpp>
#include <mcs/core/core.hpp>
#include <stdexcept>

struct Networking_Internal: public mcs::modules::Networking
{
public:
    Networking_Internal(void* core)
    {
        m_Core = reinterpret_cast<mcs::modules::Core*>(core);
        m_Logger = reinterpret_cast<mcs::modules::Logger*>(m_Core->get_module("logger"));
    
        if(!m_Logger)
        {
            throw std::runtime_error("Logger instance not found");
        }
    }

    void* create_server(short port)
    {
        return new TcpListener(port, m_Logger);
    }

    void delete_server(void* server)
    {
        auto listener_ptr = static_cast<TcpListener*>(server);

        delete listener_ptr;
    }

private:
    mcs::modules::Logger* m_Logger;
    mcs::modules::Core* m_Core;
};

CREATE_MODULE_IMPL(Networking);