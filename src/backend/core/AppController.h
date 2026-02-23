#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include <QString>
#include <QtStateMachine/QStateMachine>
#include <QSettings>
#include <QTimer>
#include <QDir>
#include <QDebug>

class AppController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentState READ currentState NOTIFY currentStateChanged)
    Q_PROPERTY(QString workspacePath READ workspacePath NOTIFY workspacePathChanged)

public:
    explicit AppController(QObject *parent = nullptr);

    QString currentState() const;
    QString workspacePath() const;

public slots:
    // This slot is called by QML when user selects a folder in the Welcome Screen
    void setWorkspacePath(const QString& path);

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
    void setCurrentState(const QString& currentState);

    QStateMachine* _machine;
    QString _currentState;
    QString _workspacePath;
    QSettings _settings;
};
#endif // APPCONTROLLER_H
