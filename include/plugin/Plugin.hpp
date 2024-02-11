#pragma once

#include <util/Version.hpp>

#include <string>

#define JEM_PLUGIN_DEF(plugin) extern "C" Plugin* _createPlugin() { return new plugin(); }

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

        void load() {
            printf("Loading Plugin %s with Version %s\n", getPluginName().c_str(), static_cast<std::string>(getPluginVersion()).c_str());
        }

        virtual ~Plugin() {}
    };
}
