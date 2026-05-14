#ifndef IWORKSPACESERVICE_H
#define IWORKSPACESERVICE_H

#include <QString>

class IWorkspaceService
{
public:
    virtual ~IWorkspaceService() = default;
    
    virtual QString getWorkspacePath() const = 0;
    virtual QString getWorkspaceName() const = 0;
    virtual void setWorkspacePath(const QString& path) = 0;
    virtual bool hasValidWorkspace() const = 0;
};

#endif // IWORKSPACESERVICE_H