#ifndef RENDER_RENDERER_HPP
#define RENDER_RENDERER_HPP

#include <core/AppModule.hpp>
#include <core/Logger.hpp>

#include <vulkan/vulkan.h>

#include <memory>
#include <vector>

namespace JEM {
  class Renderer : public AppModule {
    public:
      explicit Renderer(std::shared_ptr<Application> app);

      ~Renderer();

      auto clear() -> void {}

      auto draw() -> void {}

    private:
      VkInstance instance;
      VkDebugUtilsMessengerEXT debugMessenger;

      const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};

      auto checkValidationLayerSupport() -> bool;
      auto getRequiredExtensions() -> std::vector<const char *>;
      auto populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo) -> void;
      auto CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                        const VkAllocationCallbacks *pAllocator,
                                        VkDebugUtilsMessengerEXT *pDebugMessenger) -> VkResult;
      auto DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                         const VkAllocationCallbacks *pAllocator) -> void;

#ifdef NDEBUG
      constexpr static const bool enableValidationLayers = false;
#else
      constexpr static const bool enableValidationLayers = true;
#endif

      static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                          VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                          const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                          void *pUserData) {

        getSystemLogger()->warn("validation layer: {}", pCallbackData->pMessage);

        return VK_FALSE;
      }
  };
} // namespace JEM

#endif
