#include "AppController.h"

AppController::AppController(QObject *parent) : QObject(parent)
{
    // 1. Load data from settings
    _workspacePath = _settings.value("user/workspace", "").toString();

    // 2. Initialize and start the state machine
    setupStateMachine();
}

void AppController::setupStateMachine() {
    _machine = new QStateMachine(this);

    // Create States
    QState *initState = new QState(_machine);
    QState *welcomeState = new QState(_machine);
    QState *mainAppState = new QState(_machine);

    // --- State Entry Actions ---
    // Update the exposed QML property when states are entered
    connect(initState, &QState::entered, this, [this]() {
        setCurrentState("Init");
        // Use a timer to allow the UI to load before checking,
        // or check immediately. We check on the next event loop iteration.
        QTimer::singleShot(0, this, &AppController::checkInitialWorkspace);
    });

    connect(welcomeState, &QState::entered, this, [this]() {
        setCurrentState("Welcome");
    });

    connect(mainAppState, &QState::entered, this, [this]() {
        setCurrentState("MainWorkspace");
    });

    // --- State Transitions ---
    // From Init -> either Welcome or Main
    initState->addTransition(this, &AppController::checkCompletedNeedsSetup, welcomeState);
    initState->addTransition(this, &AppController::checkCompletedReady, mainAppState);

    // From Welcome -> Main (triggered when user selects a folder)
    welcomeState->addTransition(this, &AppController::workspaceConfigured, mainAppState);

    // Start the machine
    _machine->setInitialState(initState);
    _machine->start();
}

void AppController::checkInitialWorkspace() {
    if (!_workspacePath.isEmpty() && QDir(_workspacePath).exists()) {
        emit checkCompletedReady(); // Drives machine to mainAppState
    } else {
        emit checkCompletedNeedsSetup(); // Drives machine to welcomeState
    }
}

void AppController::setWorkspacePath(const QString &path) {
    // Clean up file:/// prefix
    QString cleanPath = path;
    if (cleanPath.startsWith("file://")) cleanPath.remove(0, 7);
#ifdef Q_OS_WIN
    if (cleanPath.startsWith("/")) cleanPath.remove(0, 1);
#endif

    _workspacePath = cleanPath;
    _settings.setValue("user/workspace", _workspacePath);
    emit workspacePathChanged();

    // Tell the state machine the user finished setup
    emit workspaceConfigured();
}

void AppController::setCurrentState(const QString &stateName) {
    if (_currentState != stateName) {
        _currentState = stateName;
        qDebug() << "App State Changed to:" << _currentState;
        emit currentStateChanged();
    }
}
