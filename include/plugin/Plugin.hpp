#pragma once

#include <util/Version.hpp>

#include <string>

#define JEM_PLUGIN_DEF(plugin) std::shared_ptr<Plugin> _createPlugin() { return std::make_shared<plugin>(); }

namespace JEM
{
    class Plugin
    {
    public:
        virtual std::string getPluginName() = 0;
        virtual Version getPluginVersion() {
            return {0, 0, 0};
        }

        virtual void init() = 0;
        virtual void update() = 0;
    };
}
