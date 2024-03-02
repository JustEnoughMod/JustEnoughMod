#ifndef PLUGIN_PLUGIN_HPP
#define PLUGIN_PLUGIN_HPP

#include <core/Logger.hpp>
#include <util/Version.hpp>

#define JEM_PLUGIN_DEF(plugin) (extern "C" Plugin * _createPlugin() { return new plugin(); })

namespace JEM {
  class Plugin {
    public:
      virtual ~Plugin() = default;

      virtual constexpr auto getPluginName() -> const char * = 0;
      virtual constexpr auto getPluginVersion() -> Version {
        return "0.0.0";
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
