#include "WorkspaceViewModel.h"
#include "../../core/ServiceProvider.h"

// Factory for QML Singleton
WorkspaceViewModel* WorkspaceViewModel::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine)
{
    // Q_UNUSED prevents the compiler from warning us about unused parameters
    Q_UNUSED(qmlEngine)
    Q_UNUSED(jsEngine)

    // Fetch the service from the locator and inject it into the ViewModel
    return new WorkspaceViewModel(ServiceProvider::instance().workspaceService());
}

// Constructor
WorkspaceViewModel::WorkspaceViewModel(IWorkspaceService* workspaceService, QObject *parent)
    : QObject(parent), _workspaceService(workspaceService)
{
}

// Getters
QString WorkspaceViewModel::workspacePath() const
{
    return _workspaceService ? _workspaceService->getWorkspacePath() : "";
}

QString WorkspaceViewModel::workspaceName() const
{
    return _workspaceService ? _workspaceService->getWorkspaceName() : "";
}

// Setters (Slots)
void WorkspaceViewModel::setWorkspacePath(const QString& path)
{
    if (_workspaceService) {
        _workspaceService->setWorkspacePath(path);
        emit workspaceChanged();
    }
}