#include <core/Logger.hpp>

#include <spdlog/sinks/stdout_color_sinks.h>

JEM::Logger::Logger(std::string name) {
  spdlog::set_pattern("[%T] [%=24!n] [%^%-7l%$] %v");

  m_logger = spdlog::stdout_color_mt(name);
  m_logger->set_level(spdlog::level::trace);
}

JEM::Logger *JEM::getSystemLogger() {
  static Logger log("JustEnoughMod");
  return &log;
}
