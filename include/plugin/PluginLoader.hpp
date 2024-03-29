#ifndef PLUGIN_PLUGINLOADER_HPP
#define PLUGIN_PLUGINLOADER_HPP

#include <core/AppModule.hpp>
#include <plugin/Plugin.hpp>

#include <dylib.hpp>

#include <utility>

namespace JEM::Plugin {
  class PluginLoader : public AppModule {
    public:
      explicit PluginLoader(std::shared_ptr<Application> app) : AppModule(app) {}

      void loadFile(const std::string &path, const std::string &name);
      void loadFolder(const std::string &path);

      [[nodiscard]] auto getNative() const -> auto & {
        return m_pluginVec;
      }

    private:
      std::vector<std::shared_ptr<dylib>>
          m_dylibVec; // add dylib object to vector so that the Plugin doesn't outlive the Loader
      std::vector<std::shared_ptr<Plugin>> m_pluginVec;
  };
} // namespace JEM::Plugin

#endif
