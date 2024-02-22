#pragma once

#include <plugin/Plugin.hpp>

#include <dylib.hpp>

#include <vector>
#include <filesystem>

namespace JEM
{
    class PluginLoader
    {
    public:
        void loadFile(std::string path, std::string name)
        {
            auto lib = std::make_shared<dylib>(path.c_str(), name.c_str(), false);

            auto createPlugin = lib->get_function<Plugin *()>("_createPlugin");

            auto plugin = std::shared_ptr<Plugin>(createPlugin());

            plugin->load();

            m_dylibVec.push_back(lib);
            m_pluginVec.push_back(plugin);
        }

        void loadFolder(std::string path)
        {
            for (const auto &dirEntry : std::filesystem::directory_iterator(path))
                loadFile(dirEntry.path().parent_path(), dirEntry.path().filename());
        }

        auto getNative() const
        {
            return m_pluginVec;
        }

    private:
        std::vector<std::shared_ptr<dylib>> m_dylibVec; // add dylib object to vector so that the Plugin doesn't outlive the Loader
        std::vector<std::shared_ptr<Plugin>> m_pluginVec;
    };
}
