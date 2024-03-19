#include <render/Renderer.hpp>

#include <core/Application.hpp>

JEM::Renderer::Renderer(std::shared_ptr<Application> app) : AppModule(app) {
  getSystemLogger()->trace("Initializing Vulkan");

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

  uint32_t glfwExtensionCount = 0;
  const char **glfwExtensions;

  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  createInfo.enabledExtensionCount = glfwExtensionCount;
  createInfo.ppEnabledExtensionNames = glfwExtensions;
  createInfo.enabledLayerCount = 0;

  std::vector<const char *> requiredExtensions;

  for (uint32_t i = 0; i < glfwExtensionCount; i++) {
    requiredExtensions.emplace_back(glfwExtensions[i]);
  }

  requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

  createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

  createInfo.enabledExtensionCount = (uint32_t)requiredExtensions.size();
  createInfo.ppEnabledExtensionNames = requiredExtensions.data();

  if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
    getSystemLogger()->critical("Vulkan: failed to create instance!");
  }
}
