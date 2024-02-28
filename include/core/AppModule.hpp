#pragma once

#include <memory>

namespace JEM {
  class Application;

  class AppModule {
    public:
      AppModule(std::shared_ptr<Application> app) : m_app(app) {
      }

    protected:
      std::shared_ptr<Application> getApp() const {
        return m_app.lock();
      }

    private:
      std::weak_ptr<Application> m_app;
  };
} // namespace JEM
