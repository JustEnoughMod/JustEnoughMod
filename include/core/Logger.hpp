#pragma once

#include <spdlog/spdlog.h>

#include <string>

namespace JEM
{
    class Logger
    {
    public:
        Logger(std::string name);

        std::shared_ptr<spdlog::logger> getNative() const
        {
            return m_logger;
        }

    private:
        std::shared_ptr<spdlog::logger> m_logger;
    };
}
