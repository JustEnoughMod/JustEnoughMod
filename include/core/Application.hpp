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
            for (auto plugin : m_pluginLoader->getNative())
            {
                plugin->init();
            }

            while (!m_quit)
            {
                while (true)
                {
                    std::any anyEvent = m_window->pollEvent();

                    if (!anyEvent.has_value())
                        break;

                    if (std::any_cast<ExitEvent>(&anyEvent))
                        m_quit = true;
                    else if (const auto event = std::any_cast<MouseButtonPressedEvent>(&anyEvent))
                    {
                        printf("Mouse Pressed Button: %i, Clicks: %i\n", event->button, event->clicks);
                    }
                    else if (const auto event = std::any_cast<MouseButtonReleasedEvent>(&anyEvent))
                    {
                        printf("Mouse Released Button: %i, Clicks: %i\n", event->button, event->clicks);
                    }
                    else if (const auto event = std::any_cast<MouseWheelEvent>(&anyEvent))
                    {
                        printf("Mouse Wheel Direction: %i, X: %f, Y: %f\n", event->direction, event->x, event->y);
                    }
                }

                m_renderer->clear();

                for (auto plugin : m_pluginLoader->getNative())
                {
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
