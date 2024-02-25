#include <core/Application.hpp>

void JEM::Application::init(char *path) {
  m_quit = false;
  m_logger = std::make_shared<Logger>("JustEnoughMod");
  m_window = std::make_shared<Window>("JustEnoughMod", 1000, 600);
  m_renderer = std::make_shared<Renderer>(m_window);
  m_pluginLoader = std::make_shared<PluginLoader>();

  getLogger()->info("Running JustEnoughMod Version {}", static_cast<std::string>(getAppVersion()));

  getLogger()->trace("Scanning Plugin Folder");

  m_pluginLoader->loadFolder(std::string(removeAppName(path)) + "Plugins");
}

void JEM::Application::deinit() {
  m_window.reset();
  m_renderer.reset();
  m_pluginLoader.reset();
  m_logger.reset();
}

void JEM::Application::run() {
  for (auto plugin : m_pluginLoader->getNative()) {
    plugin->init();
  }

  while (!m_quit) {
    while (true) {
      std::any anyEvent = m_window->pollEvent();

      if (!anyEvent.has_value())
        break;

      if (std::any_cast<ExitEvent>(&anyEvent))
        m_quit = true;
      else if (const auto event = std::any_cast<MouseButtonPressedEvent>(&anyEvent)) {
        getLogger()->debug("Mouse Pressed Button: {}, Clicks: {}", static_cast<int>(event->button), event->clicks);
      } else if (const auto event = std::any_cast<MouseButtonReleasedEvent>(&anyEvent)) {
        getLogger()->debug("Mouse Released Button: {}, Clicks: {}", static_cast<int>(event->button), event->clicks);
      } else if (const auto event = std::any_cast<MouseWheelEvent>(&anyEvent)) {
        getLogger()->debug("Mouse Wheel Direction: {}, X: {}, Y: {}", static_cast<int>(event->direction), event->x,
                           event->y);
      }
    }

    m_renderer->clear();

    for (auto plugin : m_pluginLoader->getNative()) {
      plugin->update();
    }

    m_renderer->draw();
  }
}