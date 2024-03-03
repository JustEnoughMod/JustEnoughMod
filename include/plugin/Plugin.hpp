#ifndef PLUGIN_PLUGIN_HPP
#define PLUGIN_PLUGIN_HPP

#include <core/Logger.hpp>
#include <util/Version.hpp>

#include <memory>

#define JEM_PLUGIN_DEF(plugin)                                                                                         \
  extern "C" auto _createPlugin()->Plugin * {                                                                          \
    return new plugin();                                                                                               \
  }

namespace JEM {
  class Plugin {
    public:
      virtual ~Plugin() = default;

      [[nodiscard]] virtual constexpr auto getPluginName() -> const char * = 0;
      [[nodiscard]] virtual constexpr auto getPluginVersion() -> Version {
        return Version("0.0.0");
      }

      virtual void init() = 0;
      virtual void update() = 0;

      void load() {
        m_logger = std::make_shared<Logger>(getPluginName());
        getLogger()->info("Loading Plugin {} with Version {}", getPluginName(),
                          static_cast<std::string>(getPluginVersion()));
      }

      [[nodiscard]] auto getLogger() const -> std::shared_ptr<Logger> {
        return m_logger;
      }

    private:
      std::shared_ptr<Logger> m_logger;
  };
} // namespace JEM

#endif
