#ifndef SCHED_TASK_HPP
#define SCHED_TASK_HPP

#include <sched/TaskPool.hpp>
#include <utility>

namespace JEM {
  class Task {
    public:
      Task(std::string name, std::function<void()> func) : m_name(std::move(name)), m_func(std::move(func)){};

    private:
      std::string m_name;
      std::function<void()> m_func;
  };
} // namespace JEM

#endif
