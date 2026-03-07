#pragma once
#include <QObject>
#include <QQmlEngine>
#include "AppController.h"

// The new name for AppRegistry
class ServiceProvider : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    // QML will now know this as "ServiceProvider"
    QML_SINGLETON
    Q_PROPERTY(ICounterService* counter READ counter CONSTANT)
    Q_PROPERTY(AppController* appController READ appController CONSTANT)

public:
    static ServiceProvider& instance();
    static ServiceProvider* create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    // Getters
    AppController* appController() const;

    // Setters (Injection)
    void setAppController(AppController* appController);

private:
    explicit ServiceProvider(QObject* parent = nullptr) : QObject(parent) {}
    AppController* _appController = nullptr;
};
