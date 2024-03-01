#pragma once

#include <spdlog/spdlog.h>

#include <string>

namespace JEM {
  class Logger {
    public:
      Logger(std::string name);

      template <typename... Args>
      constexpr auto trace(spdlog::format_string_t<Args...> fmt, Args &&...args) -> void {
        return m_logger->trace(std::forward<spdlog::format_string_t<Args...>>(fmt), std::forward<Args>(args)...);
      }

      template <typename... Args>
      constexpr auto debug(spdlog::format_string_t<Args...> fmt, Args &&...args) -> void {
        return m_logger->debug(std::forward<spdlog::format_string_t<Args...>>(fmt), std::forward<Args>(args)...);
      }

      template <typename... Args>
      constexpr auto info(spdlog::format_string_t<Args...> fmt, Args &&...args) -> void {
        return m_logger->info(std::forward<spdlog::format_string_t<Args...>>(fmt), std::forward<Args>(args)...);
      }

      template <typename... Args>
      constexpr auto warn(spdlog::format_string_t<Args...> fmt, Args &&...args) -> void {
        return m_logger->warn(std::forward<spdlog::format_string_t<Args...>>(fmt), std::forward<Args>(args)...);
      }

      template <typename... Args>
      constexpr auto error(spdlog::format_string_t<Args...> fmt, Args &&...args) -> void {
        return m_logger->error(std::forward<spdlog::format_string_t<Args...>>(fmt), std::forward<Args>(args)...);
      }

    private:
      std::shared_ptr<spdlog::logger> m_logger;
  };

  Logger *getSystemLogger();
} // namespace JEM
