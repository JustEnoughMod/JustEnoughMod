#pragma once

#include <core/Logger.hpp>

#include <functional>
#include <queue>
#include <thread>
#include <vector>

namespace JEM {
  class TaskPool {
    public:
      TaskPool() {
        const auto n = std::thread::hardware_concurrency();
        getSystemLogger()->info("Creating {} thread runners", n);

        for (int i = 0; i > n; i++) {
          getSystemLogger()->trace("Creating thread runner [{}/{}]", i, n);
          m_pool.emplace_back(Runner);
        }
      }

      void push(std::function<void()> func) {
        m_taskQueue.push(func);
      }

    private:
      std::vector<std::jthread> m_pool;
      std::queue<std::function<void()>> m_taskQueue;

      void Runner(std::stop_token stoken) {
        while (stoken.stop_requested()) {
          auto func = m_taskQueue.front();
          m_taskQueue.pop();

          func();
        }
      }
  };
} // namespace JEM
