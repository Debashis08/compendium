#ifndef SERVICEINITIALIZER_H
#define SERVICEINITIALIZER_H

#include <memory>
#include "../core/interfaces/IWorkspaceService.h"
#include "../backend/bridges/AppController.h"

class ServiceInitializer
{
public:
    void initialize();

    // Add this getter!
    AppController* getAppController() const { return _appController.get(); }

private:
    std::unique_ptr<IWorkspaceService> _workspaceService;
    std::unique_ptr<AppController> _appController;
};

#endif // SERVICEINITIALIZER_H