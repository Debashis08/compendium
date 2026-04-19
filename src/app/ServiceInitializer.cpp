#include <QCoreApplication>
#include "ServiceInitializer.h"
#include "../core/ServiceProvider.h"
#include "LoggerService.h"
#include "../backend/services/WorkspaceService.h"

void ServiceInitializer::initialize()
{
    LoggerService::initialize();

    QObject::connect(qApp, &QCoreApplication::aboutToQuit, []() {
        LoggerService::cleanup();
    });

    // 1. Instantiate Concrete Services
    _workspaceService = std::make_unique<WorkspaceService>();
    
    // 2. Register with Service Provider as Interfaces
    auto& serviceProvider = ServiceProvider::instance();
    serviceProvider.setWorkspaceService(_workspaceService.get());

    // 3. Inject Services into the AppController
    _appController = std::make_unique<AppController>(_workspaceService.get());
    // serviceProvider.setAppController(_appController.get());
}