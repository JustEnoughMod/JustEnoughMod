#ifndef RENDER_RENDERER_HPP
#define RENDER_RENDERER_HPP

#include <core/AppModule.hpp>
#include <memory>

#include <vulkan/vulkan.h>

namespace JEM {
  class Renderer : public AppModule {
    public:
      explicit Renderer(std::shared_ptr<Application> app);

      ~Renderer();

      auto clear() -> void {}

      auto draw() -> void {}

    private:
      VkInstance instance;

      auto checkValidationLayerSupport() -> bool;

#ifdef NDEBUG
      constexpr static const bool enableValidationLayers = false;
#else
      constexpr static const bool enableValidationLayers = true;
#endif
  };
} // namespace JEM

#endif
