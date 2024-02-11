#pragma once 

#include <plugin/Plugin.hpp>

#include <dylib.hpp>

#include <vector>

namespace JEM
{
    class PluginLoader {
    public:
        void loadFile(std::string path) {
            auto lib = std::make_shared<dylib>("build", path.c_str());
            
            auto createPlugin = lib->get_function<Plugin*()>("_createPlugin");

            auto plugin = std::shared_ptr<Plugin>(createPlugin());

            plugin->load();

            m_dylibVec.push_back(lib);
            m_pluginVec.push_back(plugin);
        }

        auto getNative() const {
            return m_pluginVec;
        }
    private:
        std::vector<std::shared_ptr<dylib>> m_dylibVec; // add dylib object to vector so that the Plugin doesn't outlive the Loader
        std::vector<std::shared_ptr<Plugin>> m_pluginVec;
    };
}
