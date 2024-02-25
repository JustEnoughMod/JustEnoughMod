#pragma once

#include <core/Window.hpp>

namespace JEM {
  class Renderer {
    public:
      Renderer(std::shared_ptr<Window> window);

      ~Renderer() {
        bgfx::shutdown();
      }

      void clear() {
        bgfx::touch(0);
      }

      void draw() {
        bgfx::frame();
      }

    private:
  };
} // namespace JEM
