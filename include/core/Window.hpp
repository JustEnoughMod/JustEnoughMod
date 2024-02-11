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
            pd.ndt = wmi.info.x11.display;
            pd.nwh = (void *)(uintptr_t)wmi.info.x11.window;
#endif

            return pd;
        }

        std::any pollEvent()
        {
            SDL_Event event;

            if (SDL_PollEvent(&event)){
                switch (event.type)
                {
                case SDL_QUIT: 
                    return ExitEvent{};
                case SDL_MOUSEMOTION:
                    return MouseMoveEvent {
                        .windowId = event.motion.windowID,
                        .mouseId = event.motion.which,
                        .x = event.motion.x,
                        .y = event.motion.y,
                        .dx = event.motion.xrel,
                        .dy = event.motion.yrel,                      
                    };
                case SDL_MOUSEBUTTONDOWN:
                    return MouseButtonPressedEvent {
                        .windowId = event.button.windowID,
                        .mouseId = event.button.which,
                        .button = static_cast<Mouse>(event.button.button),
                        .clicks = event.button.clicks,
                        .x = event.button.x,
                        .y = event.button.y,                    
                    };
                case SDL_MOUSEBUTTONUP:
                    return MouseButtonReleasedEvent {
                        .windowId = event.button.windowID,
                        .mouseId = event.button.which,
                        .button = static_cast<Mouse>(event.button.button),
                        .clicks = event.button.clicks,
                        .x = event.button.x,
                        .y = event.button.y,                     
                    };
                case SDL_MOUSEWHEEL:
                    return MouseWheelEvent {
                        .windowId = event.wheel.windowID,
                        .mouseId = event.wheel.which,
                        .direction = static_cast<MouseWheel>(event.wheel.direction),
                        .x = event.wheel.preciseX,
                        .y = event.wheel.preciseY,                     
                    };
                default:
                    break;
                }
            }

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