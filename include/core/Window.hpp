#pragma once

#include <event/Event.hpp>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>

#include <SDL.h>
#include <SDL_syswm.h>

#include <memory>
#include <any>

namespace JEM
{
    class Window
    {
    public:
        Window(std::string title, int width, int height)
            : m_title(title)
        {
            if (m_count == 0)
            {
                initSdl();
            }
            m_count++;

            m_window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(
                                                       m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
                                                       height, SDL_WINDOW_SHOWN),
                                                   SDL_DestroyWindow);

            if (m_window.get() == nullptr)
            {
                printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
                exit(EXIT_FAILURE);
            }
        }

        ~Window()
        {
            m_count--;

            if (m_count == 0)
            {
                deinitSdl();
            }
        }

        bgfx::PlatformData getRendererBindings();

        std::any pollEvent();

        std::pair<int, int> getSize() const
        {
            int width, height;

            SDL_GetWindowSize(m_window.get(), &width, &height);

            return {width, height};
        }

        int getWidth() const
        {
            auto [width, height] = getSize();
            return width;
        }

        int getHeight() const
        {
            auto [width, height] = getSize();
            return height;
        }

        std::shared_ptr<SDL_Window> getNative() const
        {
            return m_window;
        }

    private:
        static inline unsigned int m_count = 0;
        std::shared_ptr<SDL_Window> m_window;
        std::string m_title;

        static void initSdl()
        {
            printf("SDL init\n");
            if (SDL_Init(SDL_INIT_VIDEO) < 0)
            {
                printf("SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
                exit(EXIT_FAILURE);
            }
        }

        static void deinitSdl()
        {
            printf("SDL deinit\n");
            SDL_Quit();
        }
    };
}