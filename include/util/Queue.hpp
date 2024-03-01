#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>

namespace JEM {

  template <typename T> class queue {
    public:
      void push(T item) {
        std::unique_lock<std::mutex> lock(m_mutex);

        m_queue.push(item);

        m_cond.notify_all();
      }

      T pop() {
        std::unique_lock<std::mutex> lock(m_mutex);

        m_cond.wait(lock, [this]() { return !m_queue.empty(); });

        T item = m_queue.front();
        m_queue.pop();

        return item;
      }

      bool empty() {
        std::unique_lock<std::mutex> lock(m_mutex);

        return m_queue.empty();
      }

    private:
      std::queue<T> m_queue;
      std::mutex m_mutex;
      std::condition_variable m_cond;
  };
} // namespace JEM
