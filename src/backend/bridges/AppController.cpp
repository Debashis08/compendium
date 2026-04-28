#include "AppConstants.h"
#include "AppController.h"
#include <QDebug>

AppController::AppController(IWorkspaceService* workspaceService, QObject *parent) 
    : QObject(parent), _workspaceService(workspaceService)
{
    this->setupStateMachine();
}

QString AppController::currentState() const {
    return this->_currentState;
}

void AppController::setupStateMachine()
{
    this->_machine = new QStateMachine(this); // Pass 'this' as parent to avoid memory leaks

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

    // State transitions
    initialState->addTransition(this, &AppController::checkCompletedNeedsSetup, welcomeState);
    initialState->addTransition(this, &AppController::checkCompletedReady, workspaceState);

    this->_machine->setInitialState(initialState);
    this->_machine->start();
}

void AppController::checkInitialWorkspace()
{
    // Delegate the logic to the injected service
    if(this->_workspaceService && this->_workspaceService->hasValidWorkspace()) {
        emit this->checkCompletedReady();
    } else {
        emit this->checkCompletedNeedsSetup();
    }
}

void AppController::setCurrentState(const QString& currentState)
{
    if(this->_currentState != currentState) {
        this->_currentState = currentState;
        qInfo() << "App state changed to: " << this->_currentState;
        emit this->currentStateChanged();
    }
}