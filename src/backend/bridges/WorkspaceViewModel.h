#ifndef WORKSPACEVIEWMODEL_H
#define WORKSPACEVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QtQml/qqmlregistration.h>
#include "../../core/interfaces/IWorkspaceService.h"

class WorkspaceViewModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QString workspacePath READ workspacePath NOTIFY workspaceChanged)
    Q_PROPERTY(QString workspaceName READ workspaceName NOTIFY workspaceChanged)

public:
    // Factory for QML Singleton
    static WorkspaceViewModel* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);

    // Constructor Injection
    explicit WorkspaceViewModel(IWorkspaceService* workspaceService, QObject *parent = nullptr);

    QString workspacePath() const;
    QString workspaceName() const;

public slots:
    void setWorkspacePath(const QString& path);

signals:
    void workspaceChanged();

private:
    IWorkspaceService* _workspaceService;
};

#endif // WORKSPACEVIEWMODEL_H