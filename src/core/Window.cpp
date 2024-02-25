#include <core/Window.hpp>

#include <core/Application.hpp>

// fix vscode intellisense
#ifdef __INTELLISENSE__
#pragma diag_suppress 135
#endif

JEM::Window::Window(std::string title, int width, int height) : m_title(title) {
  if (m_count == 0) {
    initSdl();
  }
  m_count++;

  m_window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                                          SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN),
                                         SDL_DestroyWindow);

  if (m_window.get() == nullptr) {
    Application().getLogger()->error("Window could not be created. SDL_Error: {}", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

bgfx::PlatformData JEM::Window::getRendererBindings() {
  SDL_SysWMinfo wmi;
  SDL_VERSION(&wmi.version);
  if (!SDL_GetWindowWMInfo(m_window.get(), &wmi)) {
    Application().getLogger()->error("SDL_SysWMinfo could not be retrieved. SDL_Error: {}", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  bgfx::PlatformData pd{};
#if BX_PLATFORM_WINDOWS
  pd.nwh = wmi.info.win.window;
#elif BX_PLATFORM_OSX
  pd.nwh = wmi.info.cocoa.window;
#elif BX_PLATFORM_LINUX
  pd.ndt = wmi.info.x11.display;
  pd.nwh = (void *)(uintptr_t)wmi.info.x11.window;
#endif

  return pd;
}

std::any JEM::Window::pollEvent() {
  SDL_Event event;

  if (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        return ExitEvent{};
      case SDL_MOUSEMOTION:
        return MouseMoveEvent{
            .windowId = event.motion.windowID,
            .mouseId = event.motion.which,
            .x = event.motion.x,
            .y = event.motion.y,
            .dx = event.motion.xrel,
            .dy = event.motion.yrel,
        };
      case SDL_MOUSEBUTTONDOWN:
        return MouseButtonPressedEvent{
            .windowId = event.button.windowID,
            .mouseId = event.button.which,
            .button = static_cast<Mouse>(event.button.button),
            .clicks = event.button.clicks,
            .x = event.button.x,
            .y = event.button.y,
        };
      case SDL_MOUSEBUTTONUP:
        return MouseButtonReleasedEvent{
            .windowId = event.button.windowID,
            .mouseId = event.button.which,
            .button = static_cast<Mouse>(event.button.button),
            .clicks = event.button.clicks,
            .x = event.button.x,
            .y = event.button.y,
        };
      case SDL_MOUSEWHEEL:
        return MouseWheelEvent{
            .windowId = event.wheel.windowID,
            .mouseId = event.wheel.which,
            .direction = static_cast<MouseWheel>(event.wheel.direction),
            .x = event.wheel.preciseX,
            .y = event.wheel.preciseY,
        };
      default:
        break;
    }
  }

  return std::any();
}

void JEM::Window::initSdl() {
  Application().getLogger()->trace("Initialize SDL");
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    Application().getLogger()->error("SDL could not initialize. SDL_Error: {}", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

void JEM::Window::deinitSdl() {
  Application().getLogger()->trace("Deinitialize SDL");
  SDL_Quit();
}
