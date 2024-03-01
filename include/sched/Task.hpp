#pragma once

#include <sched/TaskPool.hpp>

class TaskManager;

namespace JEM {
  class Task {
    public:
      Task(std::string name, std::function<void()> func) : m_name(name), m_func(func){};

    protected:
      std::string m_name;
      std::function<void()> m_func;
  };
} // namespace JEM
