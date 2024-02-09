#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>

// #define SDL_VIDEO_DRIVER_X11
#define SDL_VIDEO_DRIVER_WAYLAND

#include <SDL.h>
#include <SDL_syswm.h>

#include <stdio.h>

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    const int width = 800;
    const int height = 600;
    SDL_Window *window = SDL_CreateWindow(
        "JustEnoughMod", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
        height, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(window, &wmi))
    {
        printf(
            "SDL_SysWMinfo could not be retrieved. SDL_Error: %s\n",
            SDL_GetError());
        return 1;
    }
    bgfx::renderFrame(); // single threaded mode

    bgfx::PlatformData pd{};
#if BX_PLATFORM_WINDOWS
    pd.nwh = wmi.info.win.window;
#elif BX_PLATFORM_OSX
    pd.nwh = wmi.info.cocoa.window;
#elif BX_PLATFORM_LINUX
    // pd.ndt = wmi.info.x11.display;
    // pd.nwh = (void *)(uintptr_t)wmi.info.x11.window;

    pd.ndt = wmi.info.wl.display;
    pd.nwh = (void *)(uintptr_t)wmi.info.wl.surface;
#endif

    bgfx::Init bgfx_init;
    bgfx_init.type = bgfx::RendererType::Count; // auto choose renderer
    bgfx_init.resolution.width = width;
    bgfx_init.resolution.height = height;
    bgfx_init.resolution.reset = BGFX_RESET_VSYNC;
    bgfx_init.platformData = pd;
    bgfx::init(bgfx_init);

    bgfx::setViewClear(
        0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, width, height);

    bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);

    bool quit = false;

    while (!quit)
    {
        for (SDL_Event current_event; SDL_PollEvent(&current_event) != 0;)
        {
            if (current_event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
        }

        bgfx::touch(0);

        bgfx::dbgTextClear();

        const bgfx::Stats *stats = bgfx::getStats();

        bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");

        bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
        bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");

        bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters.", stats->width, stats->height, stats->textWidth, stats->textHeight);

        bgfx::frame();
    }

    bgfx::shutdown();

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
