#pragma once
#include <QObject>
#include <QQmlEngine>
#include "interfaces/ICounterService.h"
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
    ICounterService* counter() const;
    AppController* appController() const;

    // Setters (Injection)
    void setCounterService(ICounterService* service);
    void setAppController(AppController* appController);

private:
    explicit ServiceProvider(QObject* parent = nullptr) : QObject(parent) {}
    ICounterService* _counterService = nullptr;
    AppController* _appController = nullptr;
};
