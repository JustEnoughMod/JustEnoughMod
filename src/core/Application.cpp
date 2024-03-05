#include "pch.hpp"

#include <core/Application.hpp>

void JEM::Application::init(char *path) {
  m_quit = false;
  m_taskManager = std::make_shared<TaskManager>(shared_from_this());
  m_eventManager = std::make_shared<EventManager>(shared_from_this());
  m_window = std::make_shared<Window>(shared_from_this(), "JustEnoughMod", 1000, 600);
  m_renderer = std::make_shared<Renderer>(shared_from_this());
  m_pluginLoader = std::make_shared<PluginLoader>(shared_from_this());

  getSystemLogger()->info("Running JustEnoughMod Version {}", static_cast<std::string>(getAppVersion()));

  getSystemLogger()->trace("Scanning Plugin Folder");

  getPluginLoader()->loadFolder(std::string(removeAppName(path)) + "Plugins");
}

JEM::Application::~Application() {
  m_renderer.reset();
  m_window.reset();
  m_pluginLoader.reset();
  m_eventManager.reset();
  m_taskManager.reset();
}

void JEM::Application::run() {
  for (const auto &plugin : getPluginLoader()->getNative()) {
    plugin->init();
  }

  getSystemLogger()->trace("Using bgfx renderer: {}", bgfx::getRendererName(bgfx::getRendererType()));

  while (!m_quit) {
    while (getWindow()->pollEvent())
      ;

    while (true) {
      std::any anyEvent = getEventManager()->pop();

      if (!anyEvent.has_value()) {
        break;
      }

      if (std::any_cast<ExitEvent>(&anyEvent)) {
        getSystemLogger()->debug("Quit Event recieved, Application will close");
        m_quit = true;
      } else if (const auto event = std::any_cast<MouseButtonPressedEvent>(&anyEvent)) {
        getSystemLogger()->debug("Mouse Pressed Button: {}, Clicks: {}", static_cast<int>(event->button),
                                 event->clicks);
      } else if (const auto event = std::any_cast<MouseButtonReleasedEvent>(&anyEvent)) {
        getSystemLogger()->debug("Mouse Released Button: {}, Clicks: {}", static_cast<int>(event->button),
                                 event->clicks);
      } else if (const auto event = std::any_cast<MouseWheelEvent>(&anyEvent)) {
        getSystemLogger()->debug("Mouse Wheel Direction: {}, X: {}, Y: {}", static_cast<int>(event->direction),
                                 event->x, event->y);
      }
    }

    getRenderer()->clear();

    for (const auto &plugin : getPluginLoader()->getNative()) {
      plugin->update();
    }

    getRenderer()->draw();
  }
}
