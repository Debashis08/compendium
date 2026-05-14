#include <QCoreApplication>
#include "ServiceInitializer.h"
#include "../core/ServiceProvider.h"
#include "../backend/services/LoggerService.h"
#include "../backend/services/WorkspaceService.h"

void ServiceInitializer::initialize()
{
    // Instantiate logger service.
    LoggerService::initialize();

    // Connect the signal-slot for logger service cleanup method with qApp, to log the sessions end.
    QObject::connect(qApp, &QCoreApplication::aboutToQuit, []() {
        LoggerService::cleanup();
    });

    // Instantiate Concrete Services.
    // Instantiate workspace service.
    _workspaceService = std::make_unique<WorkspaceService>();
    
    // Register with Service Provider as Interfaces.
    auto& serviceProvider = ServiceProvider::instance();
    serviceProvider.setWorkspaceService(_workspaceService.get());

    // Inject Services into the AppController
    _appController = std::make_unique<AppController>(_workspaceService.get());
    // serviceProvider.setAppController(_appController.get());
}