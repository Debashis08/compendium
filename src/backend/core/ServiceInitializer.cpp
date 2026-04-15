#include <QCoreApplication>
#include "ServiceInitializer.h"
#include "ServiceProvider.h"
#include "LoggerService.h"

void ServiceInitializer::initialize()
{
    LoggerService::initialize();

    // Register teardown hooks for graceful shutdown
    // qApp is a global pointer to the current application instance
    QObject::connect(qApp, &QCoreApplication::aboutToQuit, []() {
        LoggerService::cleanup();
    });

    // AppController creation
    _appController = std::make_unique<AppController>();
    
    // Inject into the new ServiceProvider
    auto& serviceProvider = ServiceProvider::instance();

    // serviceProvider.setCounterService(_counterService.get());
    serviceProvider.setAppController(_appController.get());
}
