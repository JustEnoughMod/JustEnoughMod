#include <core/Window.hpp>

#include <core/Application.hpp>
#include <core/Logger.hpp>
#include <event/Event.hpp>
#include <event/EventManager.hpp>

#include <GLFW/glfw3.h>

JEM::Window::Window(std::shared_ptr<Application> app, std::string title, int width, int height)
    : AppModule(app), m_title(std::move(title)) {
  if (m_count == 0) {
    getSystemLogger()->trace("Initialize GLFW");

    if (glfwInit() == 0) {
      const char *error;
      glfwGetError(&error);
      getSystemLogger()->critical("GLFW initialsation failed: {}", error);
    }

    glfwSetErrorCallback(errorCallback);
  }
  ++m_count;

  m_window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(width, height, m_title.c_str(), nullptr, nullptr),
                                         glfwDestroyWindow);

  if (m_window == nullptr) {
    const char *error;
    glfwGetError(&error);
    getSystemLogger()->critical("GLFW Window creation failed: {}", error);
  }

  glfwSetWindowUserPointer(m_window.get(), this);

  glfwSetCursorPosCallback(m_window.get(), cursorPosCallback);
  glfwSetWindowCloseCallback(m_window.get(), windowCloseCallback);
  glfwSetMouseButtonCallback(m_window.get(), mouseButtonCallback);
  glfwSetScrollCallback(m_window.get(), scrollCallback);
  glfwSetKeyCallback(m_window.get(), keyCallback);
  glfwSetCharCallback(m_window.get(), charCallback);

  glfwMakeContextCurrent(m_window.get());
}

JEM::Window::~Window() {
  --m_count;

  m_window.reset();

  if (m_count == 0) {
    getSystemLogger()->trace("Deinitialize GLFW");
    glfwTerminate();
  }
}

auto JEM::Window::getSize() const -> std::pair<int, int> {
  int width;
  int height;

  glfwGetWindowSize(m_window.get(), &width, &height);

  return {width, height};
}

auto JEM::Window::pollEvent() -> void {
  glfwSwapBuffers(m_window.get()); // TODO: SWAP TO VULKAN CODE

  glfwPollEvents();
}

auto JEM::Window::errorCallback(int error_code, const char *description) -> void {
  getSystemLogger()->error("GLFW error [{}] : {}", error_code, description);
}

auto JEM::Window::cursorPosCallback(GLFWwindow *window, double xpos, double ypos) -> void {
  auto *thisWindow = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  thisWindow->getApp()->getEventManager()->push(MouseMoveEvent{xpos, ypos});
}

auto JEM::Window::windowCloseCallback(GLFWwindow *window) -> void {
  auto *thisWindow = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  thisWindow->getApp()->getEventManager()->push(ExitEvent{});
}

auto JEM::Window::mouseButtonCallback(GLFWwindow *window, int button, int action, int /*mods*/) -> void {
  auto *thisWindow = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (action == GLFW_PRESS) {
    thisWindow->getApp()->getEventManager()->push(MouseButtonPressedEvent{static_cast<Mouse>(button)});
  } else if (action == GLFW_RELEASE) {
    thisWindow->getApp()->getEventManager()->push(MouseButtonReleasedEvent{static_cast<Mouse>(button)});
  }
}

auto JEM::Window::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) -> void {
  auto *thisWindow = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  thisWindow->getApp()->getEventManager()->push(MouseWheelEvent{xoffset, yoffset});
}

auto JEM::Window::keyCallback(GLFWwindow *window, int key, int /*scancode*/, int action, int /*mods*/) -> void {
  auto *thisWindow = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  if (action == GLFW_PRESS) {
    thisWindow->getApp()->getEventManager()->push(KeyPressedEvent{static_cast<Key>(key)});
  } else if (action == GLFW_RELEASE) {
    thisWindow->getApp()->getEventManager()->push(KeyReleasedEvent{static_cast<Key>(key)});
  }
}

auto JEM::Window::charCallback(GLFWwindow *window, unsigned int codepoint) -> void {
  auto *thisWindow = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
  thisWindow->getApp()->getEventManager()->push(TextInputEvent{codepoint});
}
