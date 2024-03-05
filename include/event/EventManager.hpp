#ifndef EVENT_EVENTMANAGER_HPP
#define EVENT_EVENTMANAGER_HPP

#include <core/AppModule.hpp>
#include <event/Event.hpp>

#include <util/Queue.hpp>

#include <any>
#include <memory>

namespace JEM {
  class EventManager : public AppModule {
    public:
      explicit EventManager(std::shared_ptr<Application> app) : AppModule(app) {}

      static void push(const std::any &event) {
        m_queue.push(event);
      }

      static auto pop() -> std::any {
        std::any event;

        if (!m_queue.empty()) {
          event = m_queue.pop();
        }

        return event;
      }

    private:
      static inline JEM::queue<std::any> m_queue;
  };
} // namespace JEM

#endif
