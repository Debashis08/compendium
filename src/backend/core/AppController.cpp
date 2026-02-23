#include "AppConstants.h"
#include "AppController.h"

AppController::AppController(QObject *parent) : QObject(parent)
{
    // Load workspace path if already set in settings
    this->_workspacePath = this->_settings.value(AppConstants::Storage::SettingsKeyWorkspace, "").toString();

    // Set up the stateMachine and the states
    this->setupStateMachine();
}

QString AppController::currentState() const
{
    return this->_currentState;
}

QString AppController::workspacePath() const
{
    return this->_workspacePath;
}

void AppController::setupStateMachine()
{
    // Create the stateMachine.
    this->_machine = new QStateMachine();

    // Create the states.
    QState* initialState = new QState(this->_machine);
    QState* welcomeState = new QState(this->_machine);
    QState* workspaceState = new QState(this->_machine);


    connect(initialState, &QState::entered, this, [this] () {
        this->setCurrentState("initialState");
        QTimer::singleShot(AppConstants::Storage::LoadingScreenTime, this, &AppController::checkInitialWorkspace);
    });

    connect(welcomeState, &QState::entered, this, [this] () {
        this->setCurrentState("welcomeState");
    });

    connect(workspaceState, &QState::entered, this, [this] () {
        this->setCurrentState("workspaceState");
    });

    // State transitions.
    // From initialState -> either welcomeState or workspaceState
    initialState->addTransition(this, &AppController::checkCompletedNeedsSetup, welcomeState);
    initialState->addTransition(this, &AppController::checkCompletedReady, workspaceState);

    // From welcomState -> workspaceState, when initially user was on welcome screen, user selected a folder as workspace
    welcomeState->addTransition(this, &AppController::workspaceConfigured, workspaceState);

    // Set the initial state in the machine.
    this->_machine->setInitialState(initialState);

    // Start the state machine.
    this->_machine->start();
}

void AppController::checkInitialWorkspace()
{
    if(!this->_workspacePath.isEmpty() && QDir(this->_workspacePath).exists())
    {
        emit this->checkCompletedReady();
    }
    else
    {
        emit this->checkCompletedNeedsSetup();
    }
}

void AppController::setCurrentState(const QString& currentState)
{
    if(this->_currentState != currentState)
    {
        this->_currentState = currentState;
    }
    qInfo() << "App state changed to: "<<this->_currentState;
    emit this->currentStateChanged();
}

void AppController::setWorkspacePath(const QString& path)
{
    QString modifiedPath = path;
    if(modifiedPath.startsWith("file://"))
    {
        modifiedPath.remove(0, 7);
    }

#ifndef Q_OS_WIN
    if(modifiedPath.startsWith("/"))
    {
        modifiedPath.remove(0, 1);
    }
#endif

    this->_workspacePath = path;
    this->_settings.setValue(AppConstants::Storage::SettingsKeyWorkspace, this->_workspacePath);

    emit this->workspaceConfigured();
}
