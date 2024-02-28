#pragma once

#include <core/AppModule.hpp>
#include <event/Event.hpp>

#include <any>
#include <queue>

namespace JEM {
  class EventManager : public AppModule {
    public:
      EventManager(std::shared_ptr<Application> app) : AppModule(app) {
      }

      void push(const std::any &event) {
        m_queue.push(event);
      }

      std::any pop() {
        std::any event;

        if (!m_queue.empty()) {
          event = m_queue.front();
          m_queue.pop();
        }

        return event;
      }

    private:
      static inline std::queue<std::any> m_queue;
  };
} // namespace JEM
