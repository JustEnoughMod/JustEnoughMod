#include <core/Window.hpp>

#include <core/Application.hpp>
#include <core/Logger.hpp>
#include <event/EventManager.hpp>

#include <SDL.h>
#include <SDL_syswm.h>

JEM::Window::Window(std::shared_ptr<Application> app, std::string title, int width, int height)
    : AppModule(app), m_title(title) {
  if (m_count == 0) {
    getSystemLogger()->trace("Initialize SDL");

#ifdef SDL_HINT_VIDEODRIVER
    SDL_SetHint(SDL_HINT_VIDEODRIVER, "wayland,x11");
#endif

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
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
