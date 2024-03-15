#ifndef RENDER_RENDERER_HPP
#define RENDER_RENDERER_HPP

#include <core/AppModule.hpp>
#include <core/Window.hpp>

namespace JEM {
  class Renderer : public AppModule {
    public:
      explicit Renderer(std::shared_ptr<Application> app);

      ~Renderer() {}

      static void clear() {}

      static void draw() {}

    private:
  };
} // namespace JEM

#endif
