#pragma once

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>

#include <SDL.h>
#include <SDL_syswm.h>

#include <memory>
#include <any>

// #include <wayland-egl.h>

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
                init_sdl();
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
                deinit_sdl();
            }
        }

        bgfx::PlatformData getRendererBindings()
        {
            SDL_SysWMinfo wmi;
            SDL_VERSION(&wmi.version);
            if (!SDL_GetWindowWMInfo(m_window.get(), &wmi))
            {
                printf(
                    "SDL_SysWMinfo could not be retrieved. SDL_Error: %s\n",
                    SDL_GetError());
                exit(EXIT_FAILURE);
            }

            bgfx::PlatformData pd{};
#if BX_PLATFORM_WINDOWS
            pd.nwh = wmi.info.win.window;
#elif BX_PLATFORM_OSX
            pd.nwh = wmi.info.cocoa.window;
#elif BX_PLATFORM_LINUX
            // if (wmi.subsystem == SDL_SYSWM_WAYLAND)
            // {
            //     wl_egl_window *win_impl = (wl_egl_window*)SDL_GetWindowData(m_window.get(), "wl_egl_window");
            //     if(!win_impl)
            //     {
            //         int width, height;
            //         SDL_GetWindowSize(m_window.get(), &width, &height);
            //         struct wl_surface* surface = wmi.info.wl.surface;
            //         if(!surface)
            //             exit(EXIT_FAILURE);
            //         win_impl = wl_egl_window_create(surface, width, height);
            //         SDL_SetWindowData(m_window.get(), "wl_egl_window", win_impl);
            //     }

            // pd.ndt = wmi.info.wl.display;
            // pd.nwh = (void *)(uintptr_t)win_impl;
            // }
            // else {
            pd.ndt = wmi.info.x11.display;
            pd.nwh = (void *)(uintptr_t)wmi.info.x11.window;
            // }
#endif

            return pd;
        }

        std::any pollEvent()
        {
            SDL_Event event;

            if (SDL_PollEvent(&event))
                return event;

            return std::any();
        }

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
        static unsigned int m_count;
        std::shared_ptr<SDL_Window> m_window;
        std::string m_title;

        static void init_sdl()
        {
            printf("SDL init\n");
            if (SDL_Init(SDL_INIT_VIDEO) < 0)
            {
                printf("SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
                exit(EXIT_FAILURE);
            }
        }

        static void deinit_sdl()
        {
            printf("SDL deinit\n");
            SDL_Quit();
        }
    };

    unsigned int Window::m_count = 0;
}