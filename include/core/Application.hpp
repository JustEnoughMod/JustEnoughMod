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
            : m_window("JustEnoughMods", 1000, 600), m_renderer(m_window)
        {
            m_pluginLoader.loadFile("./libJustEnoughModCore");
        }

        void run()
        {
            bgfx::setDebug(BGFX_DEBUG_TEXT | BGFX_DEBUG_STATS);

            while (!m_quit)
            {
                while (true)
                {
                    std::any event = m_window.pollEvent();

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

                m_renderer.clear();

                bgfx::dbgTextClear();

                const bgfx::Stats *stats = bgfx::getStats();

                bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");

                bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
                bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");

                bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters.", stats->width, stats->height, stats->textWidth, stats->textHeight);

                m_renderer.draw();
            }
        }

    private:
        Window m_window;
        Renderer m_renderer;
        PluginLoader m_pluginLoader;

        bool m_quit = false;
    };
}
