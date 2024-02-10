#include <JustEnoughMod.hpp>

#include <stdio.h>

int main(int argc, char **argv)
{
    const int width = 1000;
    const int height = 600;

    JEM::Window window("JustEnoughMods", width, height);

    bgfx::Init bgfx_init;
    bgfx_init.type = bgfx::RendererType::Count; // auto choose renderer
    bgfx_init.resolution.width = width;
    bgfx_init.resolution.height = height;
    bgfx_init.resolution.reset = BGFX_RESET_VSYNC;
    bgfx_init.platformData = window.getRendererBindings();
    bgfx::init(bgfx_init);

    bgfx::setViewClear(
        0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, width, height);

    bgfx::setDebug(BGFX_DEBUG_TEXT | BGFX_DEBUG_STATS);

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

    return 0;
}
