#pragma once

#include <core/AppModule.hpp>
#include <event/Event.hpp>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>

#include <any>
#include <memory>

namespace JEM {
  class Window : public AppModule {
    public:
      Window(std::shared_ptr<Application> app, std::string title, int width, int height);

      ~Window();

      bgfx::PlatformData getRendererBindings();

      bool pollEvent();

      std::pair<int, int> getSize() const;

      int getWidth() const {
        auto [width, height] = getSize();
        return width;
      }

      int getHeight() const {
        auto [width, height] = getSize();
        return height;
      }

      std::shared_ptr<SDL_Window> getNative() const {
        return m_window;
      }

    private:
      static inline unsigned int m_count = 0;
      std::shared_ptr<SDL_Window> m_window;
      std::string m_title;
  };
} // namespace JEM
