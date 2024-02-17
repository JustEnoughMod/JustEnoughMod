#pragma once

#include <core/Window.hpp>
#include <plugin/PluginLoader.hpp>
#include <render/Renderer.hpp>

namespace JEM
{

    class Application
    {
    public:
        Application()
        {
            m_window = std::make_shared<Window>("JustEnoughMods", 1000, 600);
            m_renderer = std::make_shared<Renderer>(m_window);
            m_pluginLoader = std::make_shared<PluginLoader>();

            m_pluginLoader->loadFile("JustEnoughModCore");
        }

        void run();

    private:
        std::shared_ptr<Window> m_window;
        std::shared_ptr<Renderer> m_renderer;
        std::shared_ptr<PluginLoader> m_pluginLoader;

        bool m_quit = false;
    };
}
