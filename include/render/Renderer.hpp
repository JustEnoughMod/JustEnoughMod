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

        std::string prefix = "[UNKNOWN    ]";

        switch (messageType) {
          case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
            prefix = "[GENERAL    ]";
            break;
          case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
            prefix = "[VALIDATION ]";
            break;
          case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
            prefix = "[PERFORMANCE]";
            break;
        }

        switch (messageSeverity) {
          case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            getVulkanLogger()->trace("{} {}", prefix, pCallbackData->pMessage);
            break;
          case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            getVulkanLogger()->info("{} {}", prefix, pCallbackData->pMessage);
            break;
          case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            getVulkanLogger()->warn("{} {}", prefix, pCallbackData->pMessage);
            break;
          case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            getVulkanLogger()->error("{} {}", prefix, pCallbackData->pMessage);
            break;
          default:
            getVulkanLogger()->error("UNKNOWN MESSAGE SEVERITY");
            getVulkanLogger()->error("{} {}", prefix, pCallbackData->pMessage);
        }

        return VK_FALSE;
      }
  };
} // namespace JEM

#endif
