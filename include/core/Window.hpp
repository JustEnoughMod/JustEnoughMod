#ifndef CORE_WINDOW_HPP
#define CORE_WINDOW_HPP

#include <SDL.h>

#include <core/AppModule.hpp>
#include <event/Event.hpp>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>

namespace JEM {
  class Window : public AppModule {
    public:
      Window(std::shared_ptr<Application> app, std::string title, int width, int height);

      ~Window();

      auto getRendererBindings() -> bgfx::PlatformData;

      auto pollEvent() -> bool;

      [[nodiscard]] auto getSize() const -> std::pair<int, int>;

      [[nodiscard]] auto getWidth() const -> int {
        auto [width, height] = getSize();
        return width;
      }

      [[nodiscard]] auto getHeight() const -> int {
        auto [width, height] = getSize();
        return height;
      }

      [[nodiscard]] auto getNative() const -> std::shared_ptr<SDL_Window> {
        return m_window;
      }

    private:
      static inline unsigned int m_count = 0;
      std::shared_ptr<SDL_Window> m_window;
      std::string m_title;
  };
} // namespace JEM

#endif
