#ifndef RENDER_RENDERER_HPP
#define RENDER_RENDERER_HPP

#pragma once

#include <core/AppModule.hpp>
#include <core/Window.hpp>

namespace JEM {
  class Renderer : public AppModule {
    public:
      explicit Renderer(std::shared_ptr<Application> app);

      ~Renderer() {
        bgfx::shutdown();
      }

      static void clear() {
        bgfx::touch(0);
      }

      static void draw() {
        bgfx::frame();
      }

    private:
  };
} // namespace JEM

#endif
