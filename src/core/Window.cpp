#include <core/Window.hpp>

#include <core/Application.hpp>
#include <core/Logger.hpp>
#include <event/EventManager.hpp>

#include <SDL.h>
#include <SDL_syswm.h>

// fix vscode intellisense
#ifdef __INTELLISENSE__
#pragma diag_suppress 135
#endif

#include <wayland-egl.h>

JEM::Window::Window(std::shared_ptr<Application> app, std::string title, int width, int height)
    : AppModule(app), m_title(title) {
  if (m_count == 0) {
    getSystemLogger()->trace("Initialize SDL");

#ifdef SDL_HINT_VIDEODRIVER
    SDL_SetHint(SDL_HINT_VIDEODRIVER, "wayland,x11");
#endif

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) {
      getSystemLogger()->error("SDL could not initialize. SDL_Error: {}", SDL_GetError());
      exit(EXIT_FAILURE);
    }
  }
  m_count++;

  m_window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                                          SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN),
                                         SDL_DestroyWindow);

  if (m_window.get() == nullptr) {
    getSystemLogger()->error("Window could not be created. SDL_Error: {}", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

bgfx::PlatformData JEM::Window::getRendererBindings() {
  SDL_SysWMinfo wmi;
  SDL_VERSION(&wmi.version);
  if (!SDL_GetWindowWMInfo(m_window.get(), &wmi)) {
    getSystemLogger()->error("SDL_SysWMinfo could not be retrieved. SDL_Error: {}", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  bgfx::PlatformData pd{};

#if BX_PLATFORM_WINDOWS
  pd.type = bgfx::NativeWindowHandleType::Default;
  pd.nwh = wmi.info.win.window;
#elif BX_PLATFORM_OSX
  pd.type = bgfx::NativeWindowHandleType::Default;
  pd.nwh = wmi.info.cocoa.window;
#elif BX_PLATFORM_LINUX
  if (wmi.subsystem == SDL_SYSWM_WAYLAND) {
    wl_egl_window *win_impl = (wl_egl_window *)SDL_GetWindowData(m_window.get(), "wl_egl_window");
    if (!win_impl) {
      int width, height;
      SDL_GetWindowSize(m_window.get(), &width, &height);
      struct wl_surface *surface = wmi.info.wl.surface;
      if (!surface) {
        exit(EXIT_FAILURE);
      }
      win_impl = wl_egl_window_create(surface, width, height);
      SDL_SetWindowData(m_window.get(), "wl_egl_window", win_impl);
    }

    pd.type = bgfx::NativeWindowHandleType::Wayland;
    pd.ndt = wmi.info.wl.display;
    pd.nwh = (void *)(uintptr_t)win_impl;
  } else {
    pd.type = bgfx::NativeWindowHandleType::Default;
    pd.ndt = wmi.info.x11.display;
    pd.nwh = (void *)(uintptr_t)wmi.info.x11.window;
  }
#endif

  return pd;
}

JEM::Window::~Window() {
  SDL_DestroyWindow(m_window.get());

  m_count--;

  if (m_count == 0) {
    getSystemLogger()->trace("Deinitialize SDL");
    SDL_Quit();
  }
}

std::pair<int, int> JEM::Window::getSize() const {
  int width, height;

  SDL_GetWindowSize(m_window.get(), &width, &height);

  return {width, height};
}

bool JEM::Window::pollEvent() {
  SDL_Event event;

  int result = SDL_PollEvent(&event);

  if (result) {
    switch (event.type) {
      case SDL_QUIT:
        getApp()->getEventManager()->push(ExitEvent{});
        break;
      case SDL_MOUSEMOTION:
        getApp()->getEventManager()->push(MouseMoveEvent{
            .windowId = event.motion.windowID,
            .mouseId = event.motion.which,
            .x = event.motion.x,
            .y = event.motion.y,
            .dx = event.motion.xrel,
            .dy = event.motion.yrel,
        });
        break;
      case SDL_MOUSEBUTTONDOWN:
        getApp()->getEventManager()->push(MouseButtonPressedEvent{
            .windowId = event.button.windowID,
            .mouseId = event.button.which,
            .button = static_cast<Mouse>(event.button.button),
            .clicks = event.button.clicks,
            .x = event.button.x,
            .y = event.button.y,
        });
        break;
      case SDL_MOUSEBUTTONUP:
        getApp()->getEventManager()->push(MouseButtonReleasedEvent{
            .windowId = event.button.windowID,
            .mouseId = event.button.which,
            .button = static_cast<Mouse>(event.button.button),
            .clicks = event.button.clicks,
            .x = event.button.x,
            .y = event.button.y,
        });
        break;
      case SDL_MOUSEWHEEL:
        getApp()->getEventManager()->push(MouseWheelEvent{
            .windowId = event.wheel.windowID,
            .mouseId = event.wheel.which,
            .direction = static_cast<MouseWheel>(event.wheel.direction),
            .x = event.wheel.preciseX,
            .y = event.wheel.preciseY,
        });
        break;
      default:
        break;
    }
  }

  return static_cast<bool>(result);
}
