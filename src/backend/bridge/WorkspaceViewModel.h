#ifndef WORKSPACEVIEWMODEL_H
#define WORKSPACEVIEWMODEL_H

#include <QObject>
#include <QtQml/qqmlregistration.h>
#include "../core/IWorkspaceService.h"
#include "../core/ServiceProvider.h"

class WorkspaceViewModel : public QObject {
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QString workspacePath READ workspacePath NOTIFY workspaceChanged)
    Q_PROPERTY(QString workspaceName READ workspaceName NOTIFY workspaceChanged)

public:
    // Factory for QML Singleton
    static WorkspaceViewModel* create(QQmlEngine*, QJSEngine*) {
        return new WorkspaceViewModel(ServiceProvider::instance().workspaceService());
    }

    // Constructor Injection
    explicit WorkspaceViewModel(IWorkspaceService* workspaceService, QObject *parent = nullptr) 
        : QObject(parent), _workspaceService(workspaceService) {}

    QString workspacePath() const { return _workspaceService ? _workspaceService->getWorkspacePath() : ""; }
    QString workspaceName() const { return _workspaceService ? _workspaceService->getWorkspaceName() : ""; }

public slots:
    void setWorkspacePath(const QString& path) {
        if (_workspaceService) {
            _workspaceService->setWorkspacePath(path);
            emit workspaceChanged();
        }
    }

signals:
    void workspaceChanged();

private:
    IWorkspaceService* _workspaceService;
};

#endif // WORKSPACEVIEWMODEL_H