#include "spdlog/common.h"
#include <core/Logger.hpp>
#include <utility>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <string>

JEM::Logger::Logger(std::string name) : m_name(std::move(name)) {
  spdlog::set_pattern("[%T] [%=24!n] [%^%-7l%$] %v");

  m_logger = spdlog::stdout_color_mt(m_name);
  m_logger->set_level(spdlog::level::trace);
}

auto JEM::getSystemLogger() -> Logger * {
  static Logger log("JustEnoughMod");
  return &log;
}

auto JEM::getVulkanLogger() -> Logger * {
  static Logger log("JEM-Vulkan");
  return &log;
}
