#include "ServiceInitializer.h"
#include "ServiceProvider.h" // Update include!
#include "LoggerService.h"

void ServiceInitializer::initialize()
{
    LoggerService::initialize();

    _counterService = std::make_unique<CounterService>();
    // AppController creation
    _appController = std::make_unique<AppController>();
    
    // Inject into the new ServiceProvider
    auto& serviceProvider = ServiceProvider::instance();
    serviceProvider.setCounterService(_counterService.get());
    serviceProvider.setAppController(_appController.get());
}
