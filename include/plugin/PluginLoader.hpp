#pragma once

#include <plugin/Plugin.hpp>

#include <dylib.hpp>

#include <filesystem>
#include <vector>

namespace JEM {
  class PluginLoader {
    public:
      void loadFile(std::string path, std::string name);
      void loadFolder(std::string path);

      auto getNative() const {
        return m_pluginVec;
      }

    private:
      std::vector<std::shared_ptr<dylib>>
          m_dylibVec; // add dylib object to vector so that the Plugin doesn't outlive the Loader
      std::vector<std::shared_ptr<Plugin>> m_pluginVec;
  };
} // namespace JEM
