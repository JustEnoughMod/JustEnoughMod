#ifndef CORE_LOGGER_HPP
#define CORE_LOGGER_HPP

#include <spdlog/spdlog.h>

namespace JEM {
  class Logger {
    public:
      explicit Logger(std::string name);

      template <typename... Args>
      constexpr auto trace(spdlog::format_string_t<Args...> fmt, Args &&...args) -> void {
        m_logger->trace(fmt, std::forward<Args>(args)...);
      }

      template <typename... Args>
      constexpr auto debug(spdlog::format_string_t<Args...> fmt, Args &&...args) -> void {
        m_logger->debug(fmt, std::forward<Args>(args)...);
      }

      template <typename... Args>
      constexpr auto info(spdlog::format_string_t<Args...> fmt, Args &&...args) -> void {
        m_logger->info(fmt, std::forward<Args>(args)...);
      }

      template <typename... Args>
      constexpr auto warn(spdlog::format_string_t<Args...> fmt, Args &&...args) -> void {
        m_logger->warn(fmt, std::forward<Args>(args)...);
      }

      template <typename... Args>
      constexpr auto error(spdlog::format_string_t<Args...> fmt, Args &&...args) -> void {
        m_logger->error(fmt, std::forward<Args>(args)...);
      }

      template <typename... Args>
      constexpr auto critical(spdlog::format_string_t<Args...> fmt, Args &&...args) -> void {
        m_logger->critical(fmt, std::forward<Args>(args)...);
        m_logger->critical("Application exit due to critical error!");
        exit(EXIT_FAILURE);
      }

      [[nodiscard]] auto getName() const -> std::string {
        return m_name;
      }

    private:
      std::shared_ptr<spdlog::logger> m_logger;

      std::string m_name;
  };

  auto getSystemLogger() -> Logger *;
} // namespace JEM

#endif
