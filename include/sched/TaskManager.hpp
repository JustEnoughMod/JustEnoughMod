#pragma once

#include <core/AppModule.hpp>
#include <sched/Task.hpp>
#include <sched/TaskPool.hpp>

namespace JEM {
  class TaskManager : public AppModule {
    public:
      TaskManager(std::shared_ptr<Application> app) : AppModule(app), m_pool() {
        for (int i = 0; i < 10000000; i++) {
          m_pool.push([i]() { getSystemLogger()->debug("Test Task {}", i + 1); });
        }
      }

      void push(Task task) {}

    private:
      TaskPool m_pool;
      JEM::queue<Task> m_taskQueue;
  };
} // namespace JEM
