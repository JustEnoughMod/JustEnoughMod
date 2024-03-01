#pragma once

#include <core/AppModule.hpp>
#include <sched/TaskPool.hpp>

#include <chrono>

using namespace std::chrono_literals;

namespace JEM {
  class TaskManager : public AppModule {
    public:
      TaskManager(std::shared_ptr<Application> app) : AppModule(app), m_pool() {
        for (int i = 0; i < 32; i++) {
          m_pool.push([i]() {
            std::this_thread::sleep_for(3s);
            // getSystemLogger()->debug("Test Task {}", i+1);
          });
        }
      }

    private:
      TaskPool m_pool;
  };
} // namespace JEM
