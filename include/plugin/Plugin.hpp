#pragma once

#include <util/Version.hpp>

#include <iostream>
#include <string>

#define JEM_PLUGIN_DEF(plugin) \
    extern "C" Plugin *_createPlugin() { return new plugin(); }

namespace JEM
{
    class Plugin
    {
    public:
        virtual constexpr const char *getPluginName() = 0;
        virtual constexpr Version getPluginVersion()
        {
            return "0.0.0";
        }

        virtual void init() = 0;
        virtual void update() = 0;

        void load()
        {
            std::cout << "Loading Plugin " << getPluginName() << " with Version " << static_cast<std::string>(getPluginVersion()) << std::endl;
        }

        virtual ~Plugin() {}
    };
}
