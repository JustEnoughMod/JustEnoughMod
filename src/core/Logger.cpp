#include <core/Logger.hpp>

#include <spdlog/sinks/stdout_color_sinks.h>

JEM::Logger::Logger(std::string name)
{
    spdlog::set_pattern("%^[%T] %n: %v%$");

    spdlog::warn("test");

    // m_logger = spdlog::stdout_color_mt(name);
    // m_logger->set_level(spdlog::level::trace);
}