#pragma once 

#include <Plugin.hpp>

#include <dylib.hpp>

#include <vector>

namespace JEM
{
    class PluginLoader {
    public:
        void loadFile(std::string path) {
            dylib dylib(path);

            auto createPlugin = dylib.get_function<std::shared_ptr<Plugin>(void)>("_createPlugin");

            m_pluginVec.push_back(createPlugin());
        }

        std::vector<std::shared_ptr<Plugin>> getNative() {
            return m_pluginVec;
        }
    private:
        std::vector<std::shared_ptr<Plugin>> m_pluginVec;
    };
}
