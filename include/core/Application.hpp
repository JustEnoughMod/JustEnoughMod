#pragma once

#include <core/Window.hpp>
#include <event/EventManager.hpp>
#include <plugin/PluginLoader.hpp>
#include <render/Renderer.hpp>

namespace JEM {
  class Application : public std::enable_shared_from_this<Application> {
    public:
      void init(char *path);
      ~Application();

      void run();

      static constexpr Version getAppVersion() {
#ifdef VERSION
        return VERSION;
#else
        return "0.0.0";
#endif
      }

      std::shared_ptr<Window> getWindow() const {
        return m_window.lock();
      }

      std::shared_ptr<Renderer> getRenderer() const {
        return m_renderer.lock();
      }

      std::shared_ptr<PluginLoader> getPluginLoader() const {
        return m_pluginLoader.lock();
      }

      std::shared_ptr<EventManager> getEventManager() const {
        return m_eventManager.lock();
      }

    private:
      std::weak_ptr<Window> m_window;
      std::weak_ptr<Renderer> m_renderer;
      std::weak_ptr<PluginLoader> m_pluginLoader;
      std::weak_ptr<EventManager> m_eventManager;

      bool m_quit;
  };
} // namespace JEM
