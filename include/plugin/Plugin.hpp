#pragma once

#include <core/Logger.hpp>
#include <util/Version.hpp>

#include <iostream>
#include <string>

#define JEM_PLUGIN_DEF(plugin)                                                                                         \
  extern "C" Plugin *_createPlugin() {                                                                                 \
    return new plugin();                                                                                               \
  }

namespace JEM {
  class Plugin {
    public:
      virtual ~Plugin() {}

      virtual constexpr const char *getPluginName() = 0;
      virtual constexpr Version getPluginVersion() {
        return "0.0.0";
      }

      virtual void init() = 0;
      virtual void update() = 0;

      void load() {
        m_logger = std::make_shared<Logger>(getPluginName());
        getLogger()->info("Loading Plugin {} with Version {}", getPluginName(),
                          static_cast<std::string>(getPluginVersion()));
      }

      std::shared_ptr<Logger> getLogger() const {
        return m_logger;
      }

    private:
      std::shared_ptr<Logger> m_logger;
  };
} // namespace JEM
