#pragma once

#include <core/Logger.hpp>
#include <util/Queue.hpp>

#include <condition_variable>
#include <functional>
#include <thread>
#include <vector>

namespace JEM {
  class TaskPool {
    public:
      TaskPool(unsigned int count = std::jthread::hardware_concurrency()) {
        getSystemLogger()->info("Creating {} thread runners", count);

        for (int i = 0; i < count; i++) {
          m_pool.emplace_back(std::bind_front(&TaskPool::Runner, this), i + 1);
        }
      }

      void push(std::function<void()> func) {
        m_taskQueue.push(func);
      }

      ~TaskPool() {
        getSystemLogger()->info("Destroy {} thread runners", m_pool.size());

        for (auto &thread : m_pool) {
          thread.request_stop();
        }
        m_cond.notify_all();
      }

    private:
      std::vector<std::jthread> m_pool;
      JEM::queue<std::function<void()>> m_taskQueue;

      std::mutex m_mutex;
      std::condition_variable m_cond;

      void Runner(const std::stop_token token, int id) {
        // getSystemLogger()->trace("Creating task runner [{}/{}]", id, m_pool.size());

        while (!token.stop_requested()) {
          {
            std::unique_lock<std::mutex> lock(m_mutex);

            m_cond.wait(lock, [this, &token]() { return !m_taskQueue.empty() || token.stop_requested(); });

            lock.unlock();
            m_cond.notify_one();
          }

          if (!m_taskQueue.empty() && !token.stop_requested()) {
            auto func = m_taskQueue.pop();

            // getSystemLogger()->debug("Recieved Task: Runner {}", id);

            func();
          }
        }

        // getSystemLogger()->trace("Destroying task runner [{}/{}]", id, m_pool.size());
      }
  };
} // namespace JEM
