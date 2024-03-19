#ifndef RENDER_RENDERER_HPP
#define RENDER_RENDERER_HPP

#include <core/AppModule.hpp>
#include <memory>

#include <vulkan/vulkan.h>

namespace JEM {
  class Renderer : public AppModule {
    public:
      explicit Renderer(std::shared_ptr<Application> app);

      ~Renderer() = default;

      static void clear() {}

      static void draw() {}

    private:
      VkInstance instance;
  };
} // namespace JEM

#endif
