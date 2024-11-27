#pragma once
#include <asio/steady_timer.hpp>
#include <asio/executor.hpp>

namespace mcs
{
    template<typename TimerType>
    struct TimerHolder
    {
    public:
        TimerHolder(const asio::any_io_executor& executor)
            : m_Timer(executor)
        {
            m_Timer.expires_at(std::chrono::steady_clock::time_point::max());   
        }

        void cancel()
        {
            m_Timer.cancel();
        }

        void cancel_one()
        {
            m_Timer.cancel_one();
        }

    private:
        TimerType m_Timer;
    };
} // namespace mcs
