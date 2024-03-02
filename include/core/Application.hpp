#ifndef CORE_APPLICATION_HPP
#define CORE_APPLICATION_HPP

#include <core/Window.hpp>
#include <event/EventManager.hpp>
#include <plugin/PluginLoader.hpp>
#include <render/Renderer.hpp>
#include <sched/TaskManager.hpp>

namespace JEM {
  class Application : public std::enable_shared_from_this<Application> {
    public:
      void init(char *path);
      ~Application();

      void run();

      static constexpr auto getAppVersion() -> Version {
#ifdef VERSION
        return VERSION;
#else
        return "0.0.0";
#endif
      }

      auto getWindow() const -> std::shared_ptr<Window> {
        return m_window;
      }

      auto getRenderer() const -> std::shared_ptr<Renderer> {
        return m_renderer;
      }

      auto getPluginLoader() const -> std::shared_ptr<PluginLoader> {
        return m_pluginLoader;
      }

      auto getEventManager() const -> std::shared_ptr<EventManager> {
        return m_eventManager;
      }

    private:
      std::shared_ptr<Window> m_window;
      std::shared_ptr<Renderer> m_renderer;
      std::shared_ptr<PluginLoader> m_pluginLoader;
      std::shared_ptr<EventManager> m_eventManager;
      std::shared_ptr<TaskManager> m_taskManager;

      bool m_quit{};
  };
} // namespace JEM

#endif
