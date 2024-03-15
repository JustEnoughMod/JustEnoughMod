#include <core/Logger.hpp>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

JEM::Logger::Logger(const std::string &name) : m_name(name) {
  spdlog::set_pattern("[%T] [%=24!n] [%^%-7l%$] %v");

  m_logger = spdlog::stdout_color_mt(m_name);
  m_logger->set_level(spdlog::level::trace);
}

auto JEM::getSystemLogger() -> JEM::Logger * {
  static Logger log("JustEnoughMod");
  return &log;
}
