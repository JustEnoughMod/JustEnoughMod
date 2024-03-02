#ifndef CORE_APPMODULE_HPP
#define CORE_APPMODULE_HPP

#include <memory>

namespace JEM {
  class Application;

  class AppModule {
    public:
      explicit AppModule(const std::shared_ptr<Application> &app) : m_app(app){};

    protected:
      [[nodiscard]] auto getApp() const -> std::shared_ptr<Application> {
        return m_app.lock();
      }

    private:
      std::weak_ptr<Application> m_app;
  };
} // namespace JEM

#endif
