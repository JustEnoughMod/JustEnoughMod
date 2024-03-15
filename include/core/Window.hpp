#ifndef CORE_WINDOW_HPP
#define CORE_WINDOW_HPP

#include <core/AppModule.hpp>
#include <event/Event.hpp>

#include <GLFW/glfw3.h>

namespace JEM {
  class Window : public AppModule {
    public:
      Window(std::shared_ptr<Application> app, std::string title, int width, int height);

      ~Window();

      auto pollEvent() -> void;

      [[nodiscard]] auto getSize() const -> std::pair<int, int>;

      [[nodiscard]] auto getWidth() const -> int {
        auto [width, height] = getSize();
        return width;
      }

      [[nodiscard]] auto getHeight() const -> int {
        auto [width, height] = getSize();
        return height;
      }

      [[nodiscard]] auto getNative() const -> std::shared_ptr<GLFWwindow> {
        return m_window;
      }

    private:
      static inline unsigned int m_count = 0;
      std::shared_ptr<GLFWwindow> m_window;
      std::string m_title;

      static auto errorCallback(int error_code, const char *description) -> void;

      static auto cursorPosCallback(GLFWwindow *window, double xpos, double ypos) -> void;
      static auto windowCloseCallback(GLFWwindow *window) -> void;
      static auto mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) -> void;
  };
} // namespace JEM

#endif
