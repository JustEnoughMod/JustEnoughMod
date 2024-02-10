#pragma once

#include <core/Window.hpp>

namespace JEM
{
    class Renderer
    {
    public:
        Renderer(Window &window)
        {
            bgfx::Init bgfx_init;
            bgfx_init.type = bgfx::RendererType::Count; // auto choose renderer
            bgfx_init.resolution.width = window.getWidth();
            bgfx_init.resolution.height = window.getHeight();
            bgfx_init.resolution.reset = BGFX_RESET_VSYNC;
            bgfx_init.platformData = window.getRendererBindings();
            bgfx::init(bgfx_init);

            bgfx::setViewClear(
                0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
            bgfx::setViewRect(0, 0, 0, window.getWidth(), window.getHeight());
        }

        ~Renderer()
        {
            bgfx::shutdown();
        }

        void clear()
        {
            bgfx::touch(0);
        }

        void draw()
        {
            bgfx::frame();
        }

    private:
    };
}