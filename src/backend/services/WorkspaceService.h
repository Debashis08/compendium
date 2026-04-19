#ifndef WORKSPACESERVICE_H
#define WORKSPACESERVICE_H

#include "./core/interfaces/IWorkspaceService.h"
#include <QSettings>
#include <QDir>

class WorkspaceService : public IWorkspaceService
{
public:
    WorkspaceService();
    
    QString getWorkspacePath() const override;
    QString getWorkspaceName() const override;
    void setWorkspacePath(const QString& path) override;
    bool hasValidWorkspace() const override;

private:
    QSettings _settings;
    QString _workspacePath;
    QString _workspaceName;
};

#endif // WORKSPACESERVICE_H