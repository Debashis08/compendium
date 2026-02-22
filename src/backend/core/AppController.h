#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include <QString>
#include <QtStateMachine/QStateMachine>
#include <QtStateMachine/QState>
#include <QTimer>
#include <QSettings>
#include <QDir>
#include <QDebug>

class AppController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentState READ currentState NOTIFY currentStateChanged)
    Q_PROPERTY(QString workspacePath READ workspacePath NOTIFY workspacePathChanged)

public:
    explicit AppController(QObject *parent = nullptr);

    QString currentState() const { return _currentState; }
    QString workspacePath() const { return _workspacePath; }

public slots:
    // Called by QML when the user selects a folder in the Welcome screen
    void setWorkspacePath(const QString &path);

signals:
    // State machine driver signals
    void checkCompletedNeedsSetup();
    void checkCompletedReady();
    void workspaceConfigured();

    // QML notification signals
    void currentStateChanged();
    void workspacePathChanged();

private:
    void setupStateMachine();
    void checkInitialWorkspace();
    void setCurrentState(const QString &stateName);

    QStateMachine *_machine;
    QString _currentState;
    QString _workspacePath;
    QSettings _settings;
};
#endif // APPCONTROLLER_H
