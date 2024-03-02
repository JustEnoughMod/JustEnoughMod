#ifndef SCHED_TASKMANAGER_HPP
#define SCHED_TASKMANAGER_HPP

#include <core/AppModule.hpp>
#include <sched/Task.hpp>
#include <sched/TaskPool.hpp>

#include <utility>

namespace JEM {
  class TaskManager : public AppModule {
    public:
      explicit TaskManager(std::shared_ptr<Application> app) : AppModule(std::move(app)), m_pool() {
        // for (int i = 0; i < 10000000; i++) {
        //   m_pool.push([i]() { getSystemLogger()->debug("Test Task {}", i + 1); });
        // }
      }

      void push(const Task &task) {}

    private:
      TaskPool m_pool;
      JEM::queue<Task> m_taskQueue;
  };
} // namespace JEM

#endif
