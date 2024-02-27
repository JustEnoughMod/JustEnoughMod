#pragma once

#include <core/AppModule.hpp>
#include <core/Window.hpp>

namespace JEM {
  class Renderer : public AppModule {
    public:
      Renderer(std::shared_ptr<Application> app);

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
