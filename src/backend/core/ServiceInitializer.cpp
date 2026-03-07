#include "ServiceInitializer.h"
#include "ServiceProvider.h"
#include "LoggerService.h"

void ServiceInitializer::initialize()
{
    LoggerService::initialize();

    // AppController creation
    _appController = std::make_unique<AppController>();
    
    // Inject into the new ServiceProvider
    auto& serviceProvider = ServiceProvider::instance();

    // serviceProvider.setCounterService(_counterService.get());
    serviceProvider.setAppController(_appController.get());
}
