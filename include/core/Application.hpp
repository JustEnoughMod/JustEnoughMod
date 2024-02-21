#pragma once

#include <core/Window.hpp>
#include <plugin/PluginLoader.hpp>
#include <render/Renderer.hpp>

namespace JEM
{
    class Application
    {
    public:
        void init(char *path);
        void run();

    private:
        static inline std::shared_ptr<Window> m_window;
        static inline std::shared_ptr<Renderer> m_renderer;
        static inline std::shared_ptr<PluginLoader> m_pluginLoader;

        static inline bool m_quit;
    };
}
