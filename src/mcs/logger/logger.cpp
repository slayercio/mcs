#include <mcs/logger.hpp>
#include <mcs/core/core.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

struct Logger_Internal: public mcs::modules::Logger 
{
    Logger_Internal(void* core) 
    {
        m_Core = reinterpret_cast<mcs::modules::Core*>(core);
        m_Logger = spdlog::stdout_color_mt("console");
    }

    void info(std::string msg) 
    {
        m_Logger->info(msg);
    }

    void warn(std::string msg)
    {
        m_Logger->warn(msg);
    }

    void error(std::string msg)
    {
        m_Logger->error(msg);
    }

    void critical(std::string msg)
    {
        m_Logger->critical(msg);
    }

    void debug(std::string msg)
    {
        m_Logger->debug(msg);
    }

private:
    std::shared_ptr<spdlog::logger> m_Logger;
    mcs::modules::Core* m_Core;
};

CREATE_MODULE_IMPL(Logger);