#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include <QString>
#include <QtStateMachine/QStateMachine>
#include <QTimer>
#include "IWorkspaceService.h"

class AppController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentState READ currentState NOTIFY currentStateChanged)

public:
    // Inject the service interface
    explicit AppController(IWorkspaceService* workspaceService, QObject *parent = nullptr);

    QString currentState() const;

signals:
    void checkCompletedNeedsSetup();
    void checkCompletedReady();
    void currentStateChanged();

private slots:
    void checkInitialWorkspace();

private:
    void setupStateMachine();
    void setCurrentState(const QString& currentState);

    QStateMachine* _machine;
    QString _currentState;

    // Used for state logic, not UI
    IWorkspaceService* _workspaceService;
};
#endif // APPCONTROLLER_H