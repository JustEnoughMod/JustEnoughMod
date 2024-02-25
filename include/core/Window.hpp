#pragma once

#include <event/Event.hpp>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>

#include <SDL.h>
#include <SDL_syswm.h>

#include <any>
#include <memory>

namespace JEM {
  class Window {
    public:
      Window(std::string title, int width, int height);

      ~Window() {
        m_count--;

        if (m_count == 0) {
          deinitSdl();
        }
      }

      bgfx::PlatformData getRendererBindings();

      std::any pollEvent();

      std::pair<int, int> getSize() const {
        int width, height;

        SDL_GetWindowSize(m_window.get(), &width, &height);

        return {width, height};
      }

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

      static void initSdl();
      static void deinitSdl();
  };
} // namespace JEM
