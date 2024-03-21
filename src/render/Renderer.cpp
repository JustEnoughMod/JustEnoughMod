#include <render/Renderer.hpp>

#include <core/Application.hpp>

JEM::Renderer::Renderer(std::shared_ptr<Application> app) : AppModule(app) {
  getSystemLogger()->trace("Initializing Vulkan");

  if (enableValidationLayers && !checkValidationLayerSupport()) {
    getSystemLogger()->critical("validation layers requested, but not available!");
  }

  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "JustEnoughMod";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "JustEnoughMod";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;

  InstanceExtensions instanceExtensions = getApp()->getWindow()->getInstanceExtensions();

  createInfo.enabledExtensionCount = instanceExtensions.count;
  createInfo.ppEnabledExtensionNames = instanceExtensions.names;
  createInfo.enabledLayerCount = 0;

  std::vector<const char *> requiredExtensions;

  for (uint32_t i = 0; i < instanceExtensions.count; i++) {
    requiredExtensions.emplace_back(instanceExtensions.names[i]);
  }

  // Portability flags for MacOS
  // requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
  // createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

  createInfo.enabledExtensionCount = (uint32_t)requiredExtensions.size();
  createInfo.ppEnabledExtensionNames = requiredExtensions.data();

  if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
    getSystemLogger()->critical("Vulkan: failed to create instance!");
  }

  uint32_t extensionCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

  std::vector<VkExtensionProperties> extensions(extensionCount);
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

  getSystemLogger()->debug("available extensions:");

  for (const auto &extension : extensions) {
    getSystemLogger()->debug("\t{}", extension.extensionName);
  }
}

JEM::Renderer::~Renderer() {

  getSystemLogger()->trace("Deinitialize Vulkan");
  vkDestroyInstance(instance, nullptr);
}

auto JEM::Renderer::checkValidationLayerSupport() -> bool {
  const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};

  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  for (const char *layerName : validationLayers) {
    bool layerFound = false;

    for (const auto &layerProperties : availableLayers) {
      if (strcmp(layerName, layerProperties.layerName) == 0) {
        layerFound = true;
        break;
      }
    }

    if (!layerFound) {
      return false;
    }
  }

  return true;
}
