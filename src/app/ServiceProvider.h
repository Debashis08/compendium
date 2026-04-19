#ifndef SERVICEPROVIDER_H
#define SERVICEPROVIDER_H

#include <QObject>
#include "IWorkspaceService.h"
#include "AppController.h"

class ServiceProvider : public QObject {
    Q_OBJECT
public:
    static ServiceProvider& instance();

    void setWorkspaceService(IWorkspaceService* service) { _workspaceService = service; }
    IWorkspaceService* workspaceService() const { return _workspaceService; }

    void setAppController(AppController* appController) { _appController = appController; }
    AppController* appController() const { return _appController; }

private:
    ServiceProvider() = default;
    
    IWorkspaceService* _workspaceService = nullptr;
    AppController* _appController = nullptr;
};

#endif // SERVICEPROVIDER_H