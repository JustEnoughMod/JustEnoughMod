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

        void run()
        {
            for (auto plugin: m_pluginLoader->getNative()) {
                plugin->init();
            }

            while (!m_quit)
            {
                while (true)
                {
                    std::any event = m_window->pollEvent();

                    if (!event.has_value())
                        break;

                    if (const auto sdlEvent = std::any_cast<SDL_Event>(&event))
                    {
                        if (sdlEvent->type == SDL_QUIT)
                        {
                            m_quit = true;
                            break;
                        }
                    }
                }

                m_renderer->clear();

                for (auto plugin: m_pluginLoader->getNative()) {
                    plugin->update();
                }

                m_renderer->draw();
            }
        }

    private:
        std::shared_ptr<Window> m_window;
        std::shared_ptr<Renderer> m_renderer;
        std::shared_ptr<PluginLoader> m_pluginLoader;

        bool m_quit = false;
    };
}
