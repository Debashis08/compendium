#include "WorkspaceService.h"
#include "./bridge/AppConstants.h" // Assumes AppConstants::Storage::SettingsKeyWorkspace is defined here
#include <QStringList>

WorkspaceService::WorkspaceService() 
{
    // Load workspace path if already set in settings [cite: 127]
    _workspacePath = _settings.value(AppConstants::Storage::SettingsKeyWorkspace, "").toString();

    // Calculate the workspace name at startup if a path exists[cite: 128].
    if(!_workspacePath.isEmpty())
    {
        QStringList modifiedPathSplit = _workspacePath.split("/");
        _workspaceName = modifiedPathSplit.last(); [cite: 129]
    }
    else
    {
        _workspaceName = "No Workspace"; [cite: 130]
    }
}

QString WorkspaceService::getWorkspacePath() const 
{
    return _workspacePath;
}

QString WorkspaceService::getWorkspaceName() const 
{
    return _workspaceName;
}

void WorkspaceService::setWorkspacePath(const QString& path) 
{
    QString modifiedPath = path;
    
    // Sanitize the file path if it comes from a QML FileDialog
    if(modifiedPath.startsWith("file://"))
    {
        modifiedPath.remove(0, 7); [cite: 146]
    }

#ifdef Q_OS_WIN
    if(modifiedPath.startsWith("/"))
    {
        modifiedPath.remove(0, 1); [cite: 147]
    }
#endif

    _workspacePath = modifiedPath;
    
    // Extract the folder name from the path
    QStringList modifiedPathSplit = modifiedPath.split("/");
    _workspaceName = modifiedPathSplit.last();
    
    // Persist the new workspace path to QSettings [cite: 148]
    _settings.setValue(AppConstants::Storage::SettingsKeyWorkspace, _workspacePath);
}

bool WorkspaceService::hasValidWorkspace() const 
{
    // Validate that the string is not empty and the directory actually exists on disk
    return (!_workspacePath.isEmpty() && QDir(_workspacePath).exists()); [cite: 141]
}